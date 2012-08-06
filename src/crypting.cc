#include "crypting.hh"

#include <sstream>
#include <iomanip>

#include <openssl/sha.h>

#include "md5.hh"

using namespace std;

namespace doctor {

/**
 * For now we'll use md5 as hash algorithm.
 */
string hash(const string& Message)
{
	return MD5(Message).hexdigest();
}

string sha256(const string& Message)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, Message.c_str(), Message.size());
	SHA256_Final(hash, &sha256);
	stringstream ss;
	for (unsigned int count = 0; count < SHA256_DIGEST_LENGTH; ++count)
		ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[count]);
	return ss.str();
}

} // namespace doctor
