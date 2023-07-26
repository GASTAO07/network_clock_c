
#include "../include/security.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/config.h"
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

int check_and_set_config_file_permissions()
{
    WCHAR *config_file_path = get_config_file_path();
    if (config_file_path == NULL)
    {
        fprintf(stderr, "Error getting file path.\n");
        return -1;
    }

    wprintf(L"Config file path: %s\n", config_file_path); // Print the file path

    HANDLE hFile = CreateFileW(config_file_path, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    free(config_file_path);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Error opening file %lu\n", GetLastError());
        return -1;
    }

    EXPLICIT_ACCESSW explicit_access[1];
    PACL acl = NULL;

    ZeroMemory(&explicit_access, sizeof(EXPLICIT_ACCESSW));
    explicit_access[0].grfAccessPermissions = GENERIC_READ | GENERIC_WRITE;
    explicit_access[0].grfAccessMode = SET_ACCESS;
    explicit_access[0].grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
    explicit_access[0].Trustee.TrusteeForm = TRUSTEE_IS_NAME;
    explicit_access[0].Trustee.TrusteeType = TRUSTEE_IS_USER;
    explicit_access[0].Trustee.ptstrName = L"Users";

    DWORD result = SetEntriesInAclW(1, explicit_access, NULL, &acl);
    if (result != ERROR_SUCCESS)
    {
        CloseHandle(hFile);
        fprintf(stderr, "Error setting ACL %lu\n", result);
        return -1;
    }

    if (!SetSecurityInfo(hFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, acl, NULL))
    {
        CloseHandle(acl);
        CloseHandle(hFile);
        fprintf(stderr, "Error setting security %lu\n", GetLastError());
        return -1;
    }
    LocalFree(acl);
    CloseHandle(hFile);
    return 0;
}


void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialize the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialize the encryption operation. In this example we are using 256 bit AES */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalize the encryption */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialize the decryption operation */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

