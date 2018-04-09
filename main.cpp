#include <winsock2.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>

static CRITICAL_SECTION cs;

#include "GX_Debug.h"
#include "XLAPI.h"
#include "GX_Global_Variables.h"
#include "GX_Server_Startup.h"
#include "GX_Server_Broadcast.h"
#include "GX_Client.h"

//Include winsock2 library
#pragma comment(lib,"WS2_32.lib")

int main(){
	//Startup debugging.
	DebugEnvironment();
	
	new_LinkedList(&users);
	new_LinkedList(&rooms);

	//Initialize an mutex lock so only one thread can access at any given time.
	InitializeCriticalSection(&cs);

	Debug.WriteLine("Checking system...");
	if(SetupWinsock()){
		int server;
		server=CreateServerSocket("10.1.1.6",1337);
		if(server!=NULL){
			Debug.WriteLine("Running and accepting connections...");
			while(true){
				listen(server,20);
				int client=accept(server,0,0);

				char *buff="<cross-domain-policy><allow-access-from domain='*' to-ports='1337' /></cross-domain-policy>";
				send(client,buff,strlen(buff)+1,0);
			
				connectionNumber++;
				Account *account=new Account;
				account->client=client;
				account->id=connectionNumber;
				account->thread=(HANDLE)_beginthread(clientThread,0,(void*)account);
			}
		}
	}
	Debug.WriteLine("Press any key to exit...");
	getchar();
	DeleteCriticalSection(&cs);
}