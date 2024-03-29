/*

  2019 정보검색 과제
  
  학번 : B354025
  이름 : 정근화

*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "dictionary.h"

using namespace std;

void printAllWordsWithDocpos(istream& in, int docpos);
bool getDocNamenDocpos(ifstream& fin, char* docname, int& docpos);

int main() {
  int docpos;                // 문서명 저장 위치
  char docname[MAXLEN + 1];  // 문서명
  ofstream irinfo;

  ifstream fin("ir.docnames");
  if (!fin) {
    cerr << "what?" << '\n';
    return 1;
  }

  try {
    /* FIXME: Different code */
    int docCnt = 0;

    while (getDocNamenDocpos(fin, docname, docpos)) {
      ifstream in(docname);
      if (!in) {
        cerr << docname << "in ir.docnames does not exist. \n";
        continue;
      }
      docCnt++;
      printAllWordsWithDocpos(in, docpos);
      in.close();
    }

    irinfo.open("ir.info", ios::out | ios::trunc);
    irinfo << docCnt << " ";

  } catch (const char* msg) {
    cout << msg << '\n';
  }
  fin.close();
}

void printAllWordsWithDocpos(istream& in, int docpos) {
  char word[MAXLEN + 1];
  int count = 0;

  while (nextNonStopWord(in, word)) {
    capital2Lower(word);
    cout << word << " ";
    cout.width(12);
    cout << docpos << '\n';
  }
}

bool getDocNamenDocpos(ifstream& fin, char* docname, int& docpos) {
  skipBlanks(fin);
  if (fin.peek() == EOF) return false;
  /* tellg -> 문서에서 현재 위치를 반환 */
  docpos = fin.tellg();

  /* 다음 공백까지 읽어서 docname 에 저장 */
  if (!(fin >> docname)) throw "Oh No!";
  return true;
}