# Basic Information

The project is a simple interface to `CredMarshalCredentialW` function and allows to make a string representation of a user's certificate. 

Mostly it would be useful in any Windows APIs allowing `marshalled credentials` like `AcquireCredentialsHandle`. This is the list of function which uses `SEC_WINNT_AUTH_IDENTITY`, `SEC_WINNT_AUTH_IDENTITY_EX` or `COAUTHIDENTITY` (if you will find any other - please write an issue and I will update the list):
1. AcquireCredentialsHandle
2. ldap_bind_s
3. ldap_sasl_bind_s
4. RpcBindingSetAuthInfo
5. CoSetProxyBlanket (with COAUTHIDENTITY structure)

Before using output from `CredMarshalCredentialW` the certificate must be placed in `Personal` (MY) certificate storage for user for current logon session. The output from `CredMarshalCredentialW` should be put in `User` field. If certificate has a `PIN` for accessing private key the `PIN` should be put in `Password` field of `SEC_WINNT_AUTH_IDENTITY`.

If you are using marshalled certificate ID in functions from above's list and `Kerberos` authentication is available then internal Windows client will try to perform `PKINIT` pre-authentication.

Also the encoded certificate hash could be using in usual interactive login to Windows. In order to do it you need to append certificate in `Personal` (MY) certificate store for SYSTEM user. It could be achived by using any `token stealer` and running `mmc.exe` as SYSTEM. Also you could run any services without any passwords and it will lead to using `User-To-User` (U2U) by such services.

The only input for the project is a DER-encoder certificate.

# Usage
```console
certMarshalCredentials.exe C:\Temp\UserCertificate.cer

@@BRi6zZsVIijBXbuYDYub3SKfcO7H
```

# License
(c) 2024, Yury Strozhevsky
[yury@strozhevsky.com](mailto:yury@strozhevsky.com)

Anyone allowed to do whatever he/she want with the code.