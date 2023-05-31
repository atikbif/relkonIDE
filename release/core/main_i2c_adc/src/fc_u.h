#ifndef FCU_H_
#define FCU_H_

#define R1_DELAY						    ( ( portTickType ) 1 / portTICK_RATE_MS )
#define R5_DELAY						    ( ( portTickType ) 5 / portTICK_RATE_MS )
#define R10_DELAY						    ( ( portTickType ) 10 / portTICK_RATE_MS )
#define R100_DELAY						    ( ( portTickType ) 100 / portTICK_RATE_MS )
#define R1000_DELAY						    ( ( portTickType ) 1000 / portTICK_RATE_MS )

#define R1_TASK_PRIORITY                    ( tskIDLE_PRIORITY + 5 )
#define R5_TASK_PRIORITY                    ( tskIDLE_PRIORITY + 4 )
#define R10_TASK_PRIORITY                   ( tskIDLE_PRIORITY + 3 )
#define R100_TASK_PRIORITY                  ( tskIDLE_PRIORITY + 2 )
#define R1000_TASK_PRIORITY                 ( tskIDLE_PRIORITY + 1 )

void R1Task( void *pvParameters );
void R5Task( void *pvParameters );
void R10Task( void *pvParameters );
void R100Task( void *pvParameters );
void R1000Task( void *pvParameters );
void Relkon_init(void);
void print_var(void);

#endif
