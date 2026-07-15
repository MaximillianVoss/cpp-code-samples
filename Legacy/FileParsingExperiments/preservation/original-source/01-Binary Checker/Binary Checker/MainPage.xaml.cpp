//
// MainPage.xaml.cpp
// Реализация класса MainPage.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <string.h>
#include <iostream>

using namespace Binary_Checker;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Provider;
using namespace Windows::Storage::Streams;
using namespace concurrency;


// Шаблон элемента пустой страницы задокументирован по адресу http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();
}


void Binary_Checker::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FileOpenPicker^ openPicker = ref new FileOpenPicker();
	openPicker->ViewMode = PickerViewMode::List;
	openPicker->SuggestedStartLocation = PickerLocationId::Desktop;
	openPicker->FileTypeFilter->Append(".bin");

	create_task(openPicker->PickMultipleFilesAsync()).then([this](IVectorView<StorageFile^>^ files)	
	{
		for each (StorageFile^ file in files)
		{
			FilesList->Items->Append(file->Name);
		}
			
	});
}

String^ GetMD5Hash(String^ fileName)
{

}


/*
String^ GetMD5HashFromFile(String^ fileName)
{
	FileStream file(fileName, FileMode::Open);
	MD5CryptoServiceProvider md5;
	array<Byte>^ retVal = md5.ComputeHash(%file);
	return Convert::ToBase64String(retVal);
}
*/





