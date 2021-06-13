#include "LCD_Functions.c"

// Dummy Data
char Total_Dis[] = "127";
char Total_Time[] = "0";
char Current_velocity[] = "5";
char Angle[] = "258";

int t_time = 0;

main(){
// initialize LCD & display default data
  LCD_init();
  LCD_Default_Data();

  // initialize port A pin 4 for turning on 100 distance led
  GPIO_PORTA_DIR_R |= 0X10;
  GPIO_PORTA_DEN_R |= 0X10;
}

void loop(){
  while(1){
  LCD_Default_Data();
  Delay(1,"sec");
  t_time = atoi(Total_Time)+1;
  itoa(t_time, Total_Time, 10);
  
  
  Total_Dis_Calc(Total_Dis);
    
  }
}

// This function will run when the total distance exceed 100m
void dis_100m(void){
  if(atoi(Total_Dis) >= 100){
    GPIO_PORTA_DATA_R |= 0X10; // power led on
  }
}
void UART1_Init(void) {
  // Enable uart clock
  SYSCTL_RCGCUART_R |= 0X02; //0000 0010

  // Enable GPIO clock
  SYSCTL_RCGCGPIO_R |= 0X04; //0000 0100
  // disable the UART for configuration
  UART1_CTL_R = 0;

  //calculate the values of the division registers
  UART1_IBRD_R = 520;
  UART1_FBRD_R = 53;
  UART1_CC_R = 0;

  // set the configuration of the line control register
  UART1_LCRH_R |= 0X70;

  //Enable the control back again
  UART1_CTL_R |= 0X0201;

  // GPIO configuration

  //enable the alternate function select
  GPIO_PORTC_AFSEL_R |= 0X30;
  // Choose the UART protocol
  GPIO_PORTC_PCTL_R |= GPIO_PCTL_PC4_U1RX | GPIO_PCTL_PC5_U1TX;
  GPIO_PORTC_DEN_R |= 0X30;

}

// claculate total distance
int Total_Dis_Calc(char Dis[]){
  int Total_distance;
  dis_100m();

  return Total_distance;
  }


// dummy data
void LCD_Default_Data(void) {
  LCD_Home();
  LCD_Write("D="); LCD_Write(Total_Dis); LCD_Write("m"); LCD_Set_Cursor(0,7); LCD_Write(",T="); LCD_Write(Total_Time); LCD_Write("s");
  LCD_Set_Cursor(1,0); LCD_Write("V="); LCD_Write(Current_velocity); LCD_Write("m/s"); LCD_Set_Cursor(1,7); LCD_Write(",A="); LCD_Write(Angle); LCD_Write("deg");
}
