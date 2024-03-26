#include <Windows.h>
#include <wincrypt.h>
#include <wincred.h>

#include <fstream>
#include <vector>
#include <iostream>
#include <string>

#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Advapi32.lib")
//***********************************************************************************************************
void process(std::wstring_view path)
{
    #pragma region Initial variables
    wchar_t* result = nullptr;

    unsigned long HashOfCertSize = CERT_HASH_LENGTH;
    CERT_CREDENTIAL_INFO CredentialInfo{ .cbSize = sizeof(CERT_CREDENTIAL_INFO) };
    #pragma endregion

    #pragma region Aux lambda
    auto error = [](std::string_view message){ std::cout << message << std::endl; };
    #pragma endregion

    #pragma region Read certificate
    std::ifstream stream(path.data(), std::ios::in | std::ios::binary | std::ios::ate);
    if(stream.is_open() == false)
        return error("Cannot open the certificate file");

    auto certificateSize = stream.tellg();
    std::vector<byte> certificate(certificateSize);

    stream.seekg(0);
    stream.read(reinterpret_cast<char*>(certificate.data()), certificateSize);
    #pragma endregion

    #pragma region Calculate certificate thumbprint and get marshalled string
    if(!CryptHashCertificate(0, CALG_SHA1, 0, certificate.data(), (unsigned long)certificate.size(), CredentialInfo.rgbHashOfCert, &HashOfCertSize))
        return error("Cannot make SHA-1 hash for the certificate");

    if(!CredMarshalCredentialW(CertCredential, &CredentialInfo, &result))
        return error("Cannot perform CredMarshalCredential for the hash");
    #pragma endregion

    std::wcout << result << std::endl;
}
//***********************************************************************************************************
int usage()
{
    std::cout << std::endl;
    std::cout << "Calculation of marshalled string for X.509 certificates" << std::endl;
    std::cout << "(c) 2024, Yury Strozhevsky (yury@strozhevsky.com)" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage: certMarshalCredential <path_to_certificate>" << std::endl;
    std::cout << std::endl;
    std::cout << "NOTE:" << std::endl;
    std::cout << "The certificate MUST be DER encoded (no BASE-64 encoded certificates allowed)" << std::endl;

    return 0;
}
//***********************************************************************************************************
int wmain(int argc, wchar_t* argv[])
{
    if(1 == argc)
        return usage();

    process(argv[1]);

    return 0;
}
//***********************************************************************************************************
