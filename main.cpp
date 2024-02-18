#include "main.hpp"

int main()
{
    cout << "---exercicio01---" << endl;
    string ex1_entrada = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

    string ex1_saida = ex01(ex1_entrada); // hexadecimal

    cout << ex1_saida << endl; // base64
    cout << "-----------------" << endl;


    cout << "---exercicio02---" << endl;
    string ex2_entrada_01 = "1c0111001f010100061a024b53535009181c";
    string ex2_entrada_02 = "686974207468652062756c6c277320657965";

    string ex2_saida = ex02(ex2_entrada_01, ex2_entrada_02); // texto1 e texto2

    cout << ex2_saida << endl; // texto1 xord texto2
    cout << "-----------------" << endl;


    cout << "---exercicio03---" << endl;
    string ex3_entrada = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    string ex3_saida = ex03(ex3_entrada); // hexadecimal criptografado

    cout << ex3_saida << endl; // mensagem descriptografada
    cout << "-----------------" << endl;


    cout << "---exercicio04---" << endl;
    string ex4_saida = ex04();
    
    cout << ex4_saida << endl; // mensagem descriptografada
    cout << "-----------------" << endl;


    cout << "---exercicio05---" << endl;
    string ex5_entrada_01 = "Burning 'em, if you ain't quick and nimbl\r\nI go crazy when I hear a cymbal";
    string ex5_entrada_02 = "ICE";

    string ex5_saida = ex05(ex5_entrada_01, ex5_entrada_02); // texto e chave

    cout << ex5_saida << endl; // mensagem criptografada 
    cout << "-----------------" << endl;


    cout << "---exercicio06---" << endl;
    string ex6_entrada = "";

    string ex6_saida = ex06();
    cout << ex6_saida << endl;

    cout << "-----------------" << endl;

}