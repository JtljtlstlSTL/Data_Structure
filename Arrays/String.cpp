class String {
 public:
  String(char* init, int m);
  bool operator==(String t);
  bool operator!();
  int Length();
  String Concat(String t);
  String Substr(int i, int j);
  int Find(String pat);
  int FastFind(String pat);
  void FailuerFunction();

 private:
  char* str;
  int len;
  int* f;
};

String::String(char* init, int m) {
  str = new char[m + 1];
  len = m;
  for (int i = 0; i < m; i++) {
    str[i] = init[i];
  }
  str[m] = '\0';
  f      = new int[len];
}

int String::Find(String pat) {
  for (int start = 0; start <= Length() - pat.Length(); start++) {
    int j;
    for (j = 0; j < pat.Length() && str[start + j] == pat.str[j]; j++) {
      if (j == pat.Length()) {
        return start;
      }
    }
  }
  return -1;
}

void String::FailuerFunction() {
  int lengthP = Length();
  f[0]        = -1;
  for (int j = 1; j < lengthP; j++) {
    int i = f[j - 1];
    while ((*(str + j) != *(str + i + 1)) && (i >= 0)) {
      i = f[i];
    }
    if (*(str + j) == *(str + i + 1)) {
      f[j] = i + 1;
    } else {
      f[j] = -1;
    }
  }
}

//时间复杂度为O(LengthS)
int String::FastFind(String pat) {
  int PosP = 0, PosS = 0;
  int LengthP = pat.Length(), LengthS = Length();
  while (PosP < LengthP && PosS < LengthS) {
    if (pat.str[PosP] == str[PosS]) {
      PosP++;
      PosS++;
    } else {
      if (PosP == 0) {
        PosS++;
      } else {
        PosP = pat.f[PosP - 1] + 1;
      };
    }
  }
  if (PosP < LengthP) {
    return -1;
  } else {
    return PosS - LengthP;
  }
}
