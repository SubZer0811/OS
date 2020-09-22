#include<stdio.h>
#include<unistd.h>

int main (){

	pid_t _2, _3;

	_2 = fork();

	if(_2 != 0){				

		_3 = fork();

		if(_3 != 0){			//This block is for 1 (main)
			printf("This is 1\n");
		}
		else{					
			pid_t _7;
			_7 = fork();

			if(_7 != 0){		//This block is for 3
				printf("This is 3\n");
			}
			else{				//This block is for 7
				printf("This is 7\n");
			}
		}
	}
	else{						
		pid_t _4;
		_4 = fork();

		if(_4 != 0){
			pid_t _5;
			_5 = fork();

			if(_5 != 0){
				pid_t _6;
				_6 = fork();

				if(_6 != 0){		//This block is for 2
					printf("This is 2\n");
				}
				else{				//This block is for 6
					printf("This is 6\n");
				}
			}
			else{
				pid_t _9;
				_9 = fork();

				if(_9 != 0){		//This block is for 5
					printf("This is 5\n");
				}
				else{				//This block is for 9
					printf("This is 9\n");
				}
			}
		}
		else{					
			
			pid_t _8;
			_8 = fork();

			if(_8 != 0){		//This block is for 4
				printf("This is 4\n");
			}
			else{				//This block is for 8
				printf("This is 8\n");
			}
		}
	}

	return 0;
}