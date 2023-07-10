# SSL RSA
SSL RSA is a cryptographic library that implements openssl [standard](#Standard) commands, [message digest](#Message-digest) commands and [cipher](#cipher) commands from scratch.

## How to compile
From the root of the repository run `make`

## How to run
After [compiling](#How-to-compile), from the root repository run `./ft_ssl [command] [options]`.

## Standard

### Commands
- genrsa: generates an RSA private key
- rsa: processes RSA keys
- rsautl: can be used to sign, verify, encrypt and decrypt data using the RSA algorithm
- gendsa: generates a DSA private key
- gendes: generates a DES key

### Options
```
ft_ssl rsa [-inform PEM] [-outform PEM] [-in file] [-passin arg] [-out file] [-passout arg] [-des] [-text] [-noout] [-modulus] [-check] [-pubin] [-pubout]
ft_ssl rsautl [-in file] [-out file] [-inkey file] [-pubin] [-encrypt] [-decrypt] [-hexdump]
genrsa, gendsa, gendes:
-i : input file
-o : output file
```

### Examples
```
$ ./ft_ssl genrsa -o private_key.pem
Generating RSA private key, 64 bit long modulus
.+++++++++++++++++++++++++++
.+++++++++++++++++++++++++++
e is 65537 (0x10001)

$ cat private_key.pem
-----BEGIN RSA PRIVATE KEY-----
MD8CAQACCQDtxqVw8Ptc0QIDAQABAggaaS+0AoHXDwIFAP7aDVcCBQDu2OYXAgUA
91y4UwIEcau8ZQIFAMguv20=
-----END RSA PRIVATE KEY-----

$ ./ft_ssl rsa -in "private_key.pem" -pubout > public_key.pem
writing RSA key

$ cat public_key.pem
-----BEGIN PUBLIC KEY-----
MCQwDQYJKoZIhvcNAQEBBQADEwAwEAIJAO3GpXDw+1zRAgMBAAE=
-----END PUBLIC KEY-----

$ ./ft_ssl rsautl -pubin -inkey public_key.pem -out encrypt.rsa -encrypt
Alice

$ ./ft_ssl rsautl -inkey private_key.pem -in encrypt.rsa  -decrypt
Alice
```

## Message Digest

### Commands
- md5
- sha224
- sha256
- sha384
- sha512

### Options
```
-p : echo STDIN to STDOUT and append the checksum to STDOUT
-q : quiet mode
-r : reverse the format of the output
-s : print the sum of the given string
```

### Examples
```
$ echo -n "Bob" | ./ft_ssl sha256
cd9fb1e148ccd8442e5aa74904cc73bf6fb54d1d54d333bd596aa9bb4bb4e961

$ echo -n "Bob" | ./ft_ssl md5
2fc1c0beb992cd7096975cfebf9d5c3b
```

## Cipher

### Commands
- base64
- des
- des-ecb
- des-cbc
- des_pcbc
- des-cfb
- des-ofb
- des3
- des3-ecb
- des3-cbc
- des3_pcbc
- des3-cfb
- des3-ofb

### Options
```
-d : decode mode
-e : encode mode (default)
-i : input file
-o : output file
des only:
-a : decode/encode the input/output in base64
-k : key in hex is the next argument
-p : password in ascii is the next argument
-s : the salt in hex is the next argument
-v : initialization vector in hex is the next argument
```

### Examples
```
$ echo "Alice's Secret" | ./ft_ssl base64
QWxpY2UncyBTZWNyZXQK

$ echo "QWxpY2UncyBTZWNyZXQK" | ./ft_ssl base64 -d
Alice's Secret

$ echo -n "Alice's Secret" | ./ft_ssl des -s "A128BE98" -o "encrypted.des"
enter encryption password:

$ hexdump encrypted.des
0000000 9d01 1da4 2ee0 e7a3 2430 7545 bcd4 4dd1
0000010

$ ./ft_ssl des -d -s "A128BE98" -i encrypted.des
enter encryption password:
Alice's Secret
```
