//
// MainPage.xaml.cpp
// Реализация класса MainPage.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <cstring>
#include <iostream>
#include <string.h>
#define NULL = false;
using namespace Xparser;
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
using namespace concurrency;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;

// Шаблон элемента пустой страницы задокументирован по адресу http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();
}


void Xparser::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FileOpenPicker^ openPicker = ref new FileOpenPicker();
	openPicker->ViewMode = PickerViewMode::List;
	openPicker->SuggestedStartLocation = PickerLocationId::Desktop;
	openPicker->FileTypeFilter->Append(".txt");

	auto dataReader = std::make_shared<DataReader^>(nullptr);

	task<StorageFile^> pickFileTask(openPicker->PickSingleFileAsync());
	pickFileTask.then(
	[this](StorageFile^ file) -> IAsyncOperation<IRandomAccessStream^>^
	{
		FileNameLabel->Text = file->Name;
		return file->OpenAsync(FileAccessMode::Read);		
	}
	).then(
	[dataReader](IRandomAccessStream^ stream) ->IAsyncOperation<unsigned int>^
	{
		*dataReader = ref new  DataReader(stream->GetInputStreamAt(0));
		return (*dataReader)->LoadAsync(stream->Size);
	}
	).then(	
		[this,dataReader](unsigned int bytes)
	{
		String ^Temp = (*dataReader)->ReadString(bytes);		
		FileContentBlock->Document->SetText(Windows::UI::Text::TextSetOptions::FormatRtf, Temp);		
		std::wstring fooW(Temp->Begin());
		TestMeth(fooW);
	}
	);		
}

void MainPage::TestMeth(std::wstring Sample)
{
	char* header[11] = { "a", "-", ".", ",", " ", "/r", ";", ":", "?", "!", "/n" };
	/*char a[11] = { '=', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<' };
	char dash[11] = { '>', '=', '>', '>', '>', '>', '>', '>', '>', '>', '>' };
	char point[11] = { '>', '>', '=', '>', '>', '>', '>', '>', '>', '>', '>' };
	char comma[11] = { '=', '>', '>', '=', '>', '>', '>', '>', '>', '>', '>' };
	char space[11] = { '=', '>', '>', '>', '=', '>', '>', '>', '>', '>', '>' };
	char end[11] = { '=', '>', '>', '>', '>', '=', '>', '>', '>', '>', '>' };
	char semicolon[11] = { '=', '>', '>', '>', '>', '>', '=', '>', '>', '>', '>' };
	char colon[11] = { '>', '=', '>', '>', '>', '>', '>', '=', '>', '>', '>' };
	char question[11] = { '>', '=', '>', '>', '>', '>', '>', '>', '=', '>', '>' };
	char exclamation[11] = { '>', '=', '>', '>', '>', '>', '>', '>', '>', '=', '>' };
	char newline[11] = { '>', '=', '>', '>', '>', '>', '>', '>', '>', '>', '=' };*/

	/*for each(Object^ Item in Sample)
	{
		WordsList->Items->Append(Item);
	}*/
	/*for each (char Item in header)
	{
		WordsList->Items->Append(Item);
	}*/
}


void Xparser::MainPage::FileNameLabel_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void Xparser::MainPage::FileContentBlock_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//Platform::String^* tempOutString2 = "";
	//FileContentBlock->Document->GetText(Windows::UI::Text::TextGetOptions::FormatRtf,tempOutString2);
		//std::wstring fooW(tempOutString->Begin());
		//TestMeth(fooW);
}
