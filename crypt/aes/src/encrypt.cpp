#include <stdio.h>
 
#include <iostream>
#include <fstream>
#include <sstream>
 
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
 
using namespace std;
using namespace CryptoPP;

byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE];
 
void initKV()
{
    // memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
    // memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );
 
    // 或者也可以

    char tmpK[] = "q1sdgj7t4e3567hr";
    char tmpIV[] = "kohs83jf0gksju3u";

    for (int j = 0; j < CryptoPP::AES::DEFAULT_KEYLENGTH; ++j)
    {
        key[j] = tmpK[j];
    }
    for (int i = 0; i < CryptoPP::AES::BLOCKSIZE; ++i)
    {
        iv[i] = tmpIV[i];
    }

}
 
string encrypt(string plainText)
{
    string cipherText;
 
    //
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv);
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( cipherText ));
    stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plainText.c_str() ), plainText.length() + 1 );
    stfEncryptor.MessageEnd();
 
    string cipherTextHex;
    for( int i = 0; i < cipherText.size(); i++ )
    {
        char ch[3] = {0};
        sprintf(ch, "%02x",  static_cast<byte>(cipherText[i]));
        cipherTextHex += ch;
    }
 
    return cipherTextHex;
}
 
 
 
void writeCipher(string output)
{
    ofstream out("./tmp/cipher.data");
    out.write(output.c_str(), output.length());
    out.close();
 
    cout<<"writeCipher finish "<<endl<<endl;
}
 
string decrypt(string cipherTextHex)
{
    string cipherText;
    string decryptedText;
    int i = 0;
    while(true)
    {
        char c;
        int x;
        stringstream ss;
        ss<<hex<<cipherTextHex.substr(i, 2).c_str();
        ss>>x;
        c = (char)x;
        cipherText += c;
        if(i >= cipherTextHex.length() - 2)break;
        i += 2;
    }
 
    //
    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );
    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedText ));
    stfDecryptor.Put( reinterpret_cast<const unsigned char*>( cipherText.c_str() ), cipherText.size());
 
    stfDecryptor.MessageEnd();
 
    return decryptedText;
}
 
string readCipher()
{
    // ifstream in("/tmp/cipher.data");
 
    string line = "a7b61a87005cd99c8b845f46d2ad1b39";
    string decryptedText;
    // while(getline(in, line))
    // {
    //     if(line.length() > 1)
    //     {
    //         decryptedText += decrypt(line) + "\n";
    //     }
    //     line.clear();
    // }
    decryptedText = decrypt(line);
    cout<<"readCipher finish "<<endl;
    // in.close();
    return decryptedText;
}
 
int main()
{
    string text = "hello";
    cout<<"text : "<<text<<endl;
 
    initKV();
    cout <<   CryptoPP::AES::DEFAULT_KEYLENGTH << endl;
    string cipherHex = encrypt(text);
    cout<<"cipher : "<<cipherHex<<endl;
    // writeCipher(cipherHex);

    string text2 = readCipher();
    cout<<"text : "<<text2<<endl;
    return 0;
}
