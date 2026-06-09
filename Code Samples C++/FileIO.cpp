//#include "pch.h"
//#include "FileIO.h"
//
//#pragma region Constructors
//FileIO::FileIO()
//{
//}
//FileIO::~FileIO()
//{
//}
//#pragma endregion
//
//#pragma region Methods
//void FileIO::WriteLines(string fileName, vector<string>lines) {
//
//	ofstream stream(&fileName[0]);
//	for (string line : lines)
//		stream.write(line.c_str(), line.size());
//	stream.close();
//}
//void FileIO::WriteLinesLn(string fileName, vector<string>lines) {
//	ofstream stream(&fileName[0]);
//	for (string line : lines) {
//		line += '\n';
//		stream.write(line.c_str(), line.size());
//	}
//	stream.close();
//}
//void FileIO::Append(string filename, vector<string>lines) {
//	vector<string>currentLines = ReadLines(filename);
//	currentLines.insert(currentLines.end(), lines.begin(), lines.end());
//	WriteLines(filename, currentLines);
//}
//vector<string> FileIO::ReadLines(string fileName)
//{
//	fstream stream(&fileName[0]);
//	string line;
//	vector<string> result;
//	while (getline(stream, line))
//		result.push_back(line);
//	stream.close();
//	return result;
//}
//vector<vector<string>> FileIO::ReadMatrix(string fileName)
//{
//	StrHelper strHelper = StrHelper();
//	vector <vector<string>> matrix;
//	vector<string> lines = ReadLines(fileName);
//	for (size_t i = 0; i < lines.size(); i++)
//		matrix.push_back(strHelper.Split(lines[i], ' '));
//	return matrix;
//}
//FILE* FileIO::OpenRead(string fileName) {
//	FILE* file = NULL;
//	fopen_s(&file, fileName.c_str(), "r");
//	return file;
//}
//string FileIO::ReadAllText(string fileName) {
//	string res = "";
//	vector<string> lines = ReadLines(fileName);
//	for (int i = 0; i < lines.size(); i++)
//		res += lines[i];
//	return res;
//}
//FILE* FileIO::OpenWrite(string fileName) {
//	FILE* file = NULL;
//	fopen_s(&file, fileName.c_str(), "w");
//	return file;
//}
//void FileIO::Close(FILE* file) {
//	if (file != NULL)
//		fclose(file);
//}
//#pragma region Remove comments
///// <summary>
///// записывает символ в выходной файл
///// </summary>
///// <param name="c">текузий символ</param>
///// <param name="input">входной файл</param>
///// <param name="output">выходной файл</param>
///// <returns></returns>
//char PutGetNext(char c, FILE* input, FILE* output) {
//	fputc(c, output);
//	return fgetc(input);
//}
//void FileIO::RemoveComments(string inFile, string outFile) {
//	FILE* input = OpenRead(inFile);
//	FILE* output = OpenWrite(outFile);
//	if (!input)
//	{
//		printf("\nНе удалось открыть файл %s для чтения", inFile.c_str());
//		fclose(output);
//	}
//	char cur = fgetc(input);
//
//	if (output)
//	{
//		if (cur != EOF)
//		{
//			while (cur != EOF)
//			{
//				if ((cur != '/') && (cur != '\"') && (cur != '\''))
//					cur = PutGetNext(cur, input, output);
//				else
//				{
//					if ((cur != '\"') && (cur != '\''))
//					{
//						cur = fgetc(input);
//						if (cur == '/' || cur == '*')
//						{
//							if (cur == EOF)
//								break;
//							if (cur == '/')
//							{
//								cur = fgetc(input);
//								while (cur != '\n')
//								{
//									if (cur == EOF)
//										break;
//									if (cur == '\\')
//									{
//										cur = fgetc(input);
//										cur = fgetc(input);
//									}
//									else
//										cur = fgetc(input);
//								}
//							}
//							else
//							{
//								cur = fgetc(input);
//								while (cur)
//								{
//									if (cur == EOF)
//										break;
//									if (cur == '*')
//									{
//										cur = fgetc(input);
//										if (cur == '/')
//										{
//											cur = fgetc(input);
//											break;
//										}
//									}
//									else
//										cur = fgetc(input);
//								}
//							}
//						}
//						else
//							fputc('/', output);
//					}
//					else
//					{
//						if (cur == '\"')
//						{
//							cur = PutGetNext(cur, input, output);
//							while (cur != '\"')
//							{
//								if (cur == EOF)
//									break;
//								if (cur == '\\')
//								{
//									cur = PutGetNext(cur, input, output);
//									cur = PutGetNext(cur, input, output);
//									if (cur == '\"')
//										break;
//								}
//								else
//								{
//									if (cur != '\n')
//										cur = PutGetNext(cur, input, output);
//									else
//										break;
//								}
//							}
//							cur = PutGetNext(cur, input, output);
//						}
//						else
//						{
//							cur = PutGetNext(cur, input, output);
//							while (cur != '\'')
//							{
//								if (cur == EOF || cur == '\'')
//									break;
//								if (cur == '\\')
//									cur = PutGetNext(cur, input, output);
//								if (cur != '\n')
//									cur = PutGetNext(cur, input, output);
//								else
//									break;
//							}
//							cur = PutGetNext(cur, input, output);
//						}
//					}
//				}
//			}
//		}
//	}
//	else
//		printf("\nНе удалось открыть файл %s для чтения", outFile.c_str());
//	printf("\nКомментарии из фалйа %s удалены, выходной файл: %s.\n", inFile.c_str(), outFile.c_str());
//	Close(input);
//	Close(output);
//}
//void FileIO::RemoveComments(FILE* in, FILE* out)
//{
//	if (in && out)
//	{
//		//текущий и предыдщий символы
//		char buff[2] = { '\0','\0' };
//		//пропуск ( пропускать текст или нет)
//		char ignore = '\0';
//		//обходим файл
//		while ((buff[0] = fgetc(in)) != EOF)
//		{
//			// проверка на начало комментария или строки
//			if (!ignore)
//			{
//				//если начался комментарий "//"
//				if ((buff[1] == '/') && (buff[0] == '/'))
//					ignore = '/';
//				//если начался комментарий "/*"
//				else if ((buff[1] == '/') && (buff[0] == '*'))
//					ignore = '*';
//				//игнорируем начало строк,но не присваивания символов
//				else if (((buff[1] != '\'') && (buff[0] == '"')) &&
//					((buff[1] != '\\') && (buff[0] == '"')))
//				{
//					fputc(buff[1], out);
//					fputc(buff[0], out);
//					ignore = '"';
//				}
//				//очищаем буфер, если стоит флаг
//				if (ignore)
//				{
//					buff[0] = '\0';
//					buff[1] = '\0';
//				}
//			}
//			//проверка на символы, которые обнуляют флаг
//			switch (ignore)
//			{
//				//если "//" ищем конец строки
//			case '/':
//				if (buff[1] == '\n')
//					ignore = '\0';
//				break;
//				//если "/*", то ищем "*/"
//			case '*':
//				if ((buff[1] == '*') && (buff[0] == '/'))
//				{
//					buff[0] = '\0';
//					buff[1] = '\0';
//					ignore = '\0';
//				}
//				break;
//				//если игнорируем строки ищем '"'
//			case '"':
//				if ((buff[1] != '\\') && (buff[0] == '"'))
//				{
//					fputc(buff[1], out);
//					fputc(ignore, out);
//					ignore = '\0';
//					buff[0] = '\0';
//					buff[1] = '\0';
//				}
//				break;
//			default:
//				break;
//			}
//			//пишем содержимое строк
//			if (ignore == '"') {
//				if (buff[1] != '\0')
//					fputc(buff[1], out);
//			}
//			//если нет флага пропуска, то пишем символ в файл 
//			if ((!(ignore)) && (buff[1]))
//				fputc(buff[1], out);
//			//смещение символов
//			//текущий становится следующим
//			buff[1] = buff[0];
//		}
//		//порверка имеется ли незакрытый комментарий комментарий или строка
//		if (ignore)
//			fprintf(stderr, "Незакрытый файл или строка\n");
//		//дописываем последний символ
//		fputc(buff[1], out);
//	}
//}
//#pragma endregion
//#pragma endregion