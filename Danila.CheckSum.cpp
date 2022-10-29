/*
 *    A digit representing the sum of the correct digits in a piece of stored or transmitted digital data,
 *    against which later comparisons can be made to detect errors in the data.
 */
	
#include <bits/stdc++.h>
using namespace std;

/**
 *\brief    A function to find the one's complement of
 *          the given binary string
 */
string Ones_complement(string data)
{
    for (int a = 0; a < data.length(); a++) {
        if (data[a] == '0')
            data[a] = '1';
        else
            data[a] = '0';
    }
    return data;
}
 
/**
 *\brief    A function to return the checksum value
 *          the given string when divided in K size blocks
 */
string checkSum(string data, int block_size)
{
    int n = data.length();
    if (n % block_size != 0) {
        int pad_size = block_size - (n % block_size);
        for (int a = 0; a < pad_size; a++) {
            data = '0' + data;
        }
    }


    string result = "";
    for (int a = 0; a < block_size; a++) {
        result += data[a];
    }
 
	/**
	 *\brief    Loop to calculate the block
     *          wise addition of data
     */
    for (int a = block_size; a < n; a += block_size) {
        string next_block = "";
        for (int j = a; j < a + block_size; j++) {
            next_block += data[j];
        }
 
        string additions = "";
        int sum = 0, carry = 0;
        
        /**
		 *\brief    Loop to calculate the binary addition of
    	 *          the current two blocks of k size
    	 */
        for (int k = block_size - 1; k >= 0; k--) {
            sum += (next_block[k] - '0')
                   + (result[k] - '0');
            carry = sum / 2;
            if (sum == 0) {
                additions = '0' + additions;
                sum = carry;
            }
            else if (sum == 1) {
                additions = '1' + additions;
                sum = carry;
            }
            else if (sum == 2) {
                additions = '0' + additions;
                sum = carry;
            }
            else {
                additions = '1' + additions;
                sum = carry;
            }
        }
 
    
        string final = "";
        if (carry == 1) {
            for (int l = additions.length() - 1; l >= 0;
                 l--) {
                if (carry == 0) {
                    final = additions[l] + final;
                }
                else if (((additions[l] - '0') + carry) % 2
                         == 0) {
                    final = "0" + final;
                    carry = 1;
                }
                else {
                    final = "1" + final;
                    carry = 0;
                }
            }
            result = final;
        }
        else {
            result = additions;
        }
    }
 
   
    return Ones_complement(result);
}
 
/**
 *\brief    A function to check if the received message
 *          is same as the senders message
 */
bool checker(string sent_message, string rec_message, int block_size)
{
    string sender_checksum = checkSum(sent_message, block_size);
    string receiver_checksum = checkSum(rec_message + sender_checksum, block_size);
 

    if (count(receiver_checksum.begin(), receiver_checksum.end(), '0') == block_size) {
        return true;
    }
    else {
        return false;
    }
}
 
 
int main()
{
	char sent_message[100]; char recv_message[100];
	
        cout<<"Sent Message: ";
    	cin>>sent_message;
        cout<<"Receive Message: ";
        cin>>recv_message;
    	int block_size = 8;
 
    if (checker(sent_message, recv_message, block_size)) {
        cout << "\nN O  E R R O R";
    }
    else {
        cout << "\nE R R O R";
    }
    return 0;
}
