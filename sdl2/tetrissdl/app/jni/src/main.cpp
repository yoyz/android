#include "Master.h"
#include "GameSdl.h"
#include <unistd.h>
#include <sys/types.h>


using namespace std;

int main(int argc, char *argv[])
{
  int pid;
  int uid;
  
  uid=getuid();
  if (uid==0)
    {
      cout << "I am root, launch me as a real user" << endl;
      exit(0);
    }

  //Seeding
  pid=getpid();
  srand(pid);
  
  game_start();
  exit(0);
}
