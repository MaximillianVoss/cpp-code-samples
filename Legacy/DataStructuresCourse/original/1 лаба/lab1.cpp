#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "XESH.h"
#include <Windows.h>

using namespace std;

int _tmain()
{
	setlocale(LC_ALL, "rus");
  srand(time(NULL));
  Set A('A'), B('B'), C('C'), D('D'), E;

  E=(A-B-C-D);
  E.Show();
  system("pause");
  return 0;
}

