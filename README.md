# Basic Information

The project is a simple interface to `CredMarshalCredentialW` function and allows to make a string representation of a user's certificate. Mostly it would be useful in any Windows APIs allowing `marshalled credentials` like `AcquireCredentialsHandle`.

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