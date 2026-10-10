 #include<iostream>
 #include<thread>
 #include<fstream>
 #include<windows.h>
using namespace std;
 void triggerFileAction() {
 Sleep(500);
 ofstream f("trigger.tmp");
 f<<"change";
 f.close();
 }

 int main(){
 HANDLE hChange=FindFirstChangeNotificationA(".",FALSE,
 FILE_NOTIFY_CHANGE_FILE_NAME|FILE_NOTIFY_CHANGE_LAST_WRITE);

 cout<<"Watching directory for modifications...\n";
 thread t(triggerFileAction);

 //Sleepwith0%CPU until thefilesystemtriggerstheevent
 WaitForSingleObject(hChange,INFINITE);
 cout<<"Directory change detected!\n";

 t.join();
 FindCloseChangeNotification(hChange);
 DeleteFileA("trigger.tmp");
 return 0;
 }
