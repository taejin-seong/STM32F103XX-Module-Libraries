## Dev environment<br>
### IDE
* STM32CubeIDE 1.6.0 <br>
* STM32CubeMX <br>
### Development Board
* **STM32F103C8T6 (Black Pill Board)** <br>



<br>


## Component<br>


|***Part Name***|***Image Link***|***Implementation***|
|---|:---:|:---:|
|**DFplayer Mini**|[📌](https://www.devicemart.co.kr/goods/view?no=1278727)|✓|
|**NRF24L01**|[📌](https://www.devicemart.co.kr/goods/view?no=12506373)|✓|
|**1602 CLCD With I2C**|[📌](https://www.devicemart.co.kr/goods/view?no=1327456)|✓|
|**8*8 Dot Matrix With MAX7219**|[📌](https://www.devicemart.co.kr/goods/view?no=1279804)|✓|



<br>



## Where's the file?<br>
<details>
<summary>:open_file_folder:</summary><br>
  
<summary>DFplayer Mini</summary>  
<div markdown="1">
<br>
-  &nbsp; stm32f103_fw_module → src → common → hw → include → dfplayer.h<br>
-  &nbsp; stm32f103_fw_module → src → hw → driver → dfplayer.c<br>
-  &nbsp; stm32f103_fw_module → src → ap → ap.c → void apDFPlayerTest(void){...}<br>
</div>
<hr/>
<summary>NRF24L01</summary>
<div markdown="1">
<br>
-  &nbsp; stm32f103_fw_module → src → common → hw → include → nrf24l01.h<br>
-  &nbsp; stm32f103_fw_module → src → hw → driver → nrf24l01.c<br>
-  &nbsp; stm32f103_fw_module → src → ap → ap.c → void apNRF24L01TxTest(void){...}<br>
-  &nbsp; stm32f103_fw_module → src → ap → ap.c → void apNRF24L01RxTest(void){...}<br> 
</div>
<hr/>
<summary>1602 CLCD With I2C</summary>
<div markdown="1">
<br>
-  &nbsp; stm32f103_fw_module → src → common → hw → include → clcd.h<br>
-  &nbsp; stm32f103_fw_module → src → hw → driver → clcd.c<br>
-  &nbsp; stm32f103_fw_module → src → ap → ap.c → void apCLCDTest(void){...}<br>
</div>
<hr/>
<summary>8*8 Dot Matrix With MAX7219</summary>
<div markdown="1">
<br>
-  &nbsp; stm32f103_fw_module → src → common → hw → include →  max7219.h<br>	
-  &nbsp; stm32f103_fw_module → src → common → hw → include →  max7219_dotmatrix.h<br>
-  &nbsp; stm32f103_fw_module → src → hw → driver → max7219.c<br>
-  &nbsp; stm32f103_fw_module → src → hw → driver → max7219_dotmatrix.c<br>	
-  &nbsp; stm32f103_fw_module → src → ap → ap.c → void apDotMatrixTest(void){...}<br>
</div>		
</details>


<br>


## Port Allocation Table<br>
<details>
<summary>📌</summary><br>
<div markdown="1">
 <p align="center">	
<img src="https://user-images.githubusercontent.com/70312248/159966974-f57bcb88-c769-4425-97d6-2144d63ca76c.png" width="500" height="500"/> <br><br>
	</p>
	</div>		
</details>

<br>


## Cube MX Setting<br>
### Clock Configuration
<details>
<summary>📌</summary><br> 
<div markdown="1">
• Using HSE (High Speed External)<br><br>
<img src="https://user-images.githubusercontent.com/70312248/156926816-cd46825e-392c-4452-a740-515ae7ccae25.png" width="800" height="500"/> <br>
<br><br>
</div>
</details>


<hr/>

### Pinout<br>
<details>
<summary>📌</summary><br>  
<div markdown="1">
	 <p align="center">
<img src="https://user-images.githubusercontent.com/70312248/159958979-4f03b977-3f47-40a6-8b74-0e6e0e05b53b.png" width="600" height="500"/> <br>
	</
		 <br><br>
</div>
</details>

<hr/>

### Peripheral & Core Configuration<br>
#### 1. UART1 & UART2

<details>
<summary>📌</summary><br>
• The parameters of uart1 & uart2 are the same<br>
• You can change parameter settings in uart.c <br><br>
<div markdown="1">
<img src="https://user-images.githubusercontent.com/70312248/156927378-6c0fd54e-bd78-437c-8f49-289d4a90c563.png" width="1000" height="600"/>
<br><br>
</div>
</details>

#### 2. SPI1 & SPI2
<details>
<summary>📌</summary><br> 
• You can change parameter settings in spi.c <br><br> 
<div markdown="1">
	<strong>SPI1</strong><br><br> 	
<img src="https://user-images.githubusercontent.com/70312248/156927368-b1cff53b-974c-42e0-80a3-1a3baf264159.png" width="1000" height="800"/>
 
<br><br>
	<strong>SPI2</strong><br><br>
<img src="https://user-images.githubusercontent.com/70312248/159957635-1bdc1f67-084f-4d28-a9c3-85821895070f.png" width="1000" height="800"/> 	
<br><br>
</div>
</details>

#### 3. I2C1
<details>
<summary>📌</summary><br> 
• You can change parameter settings in i2c.c <br><br> 
<div markdown="1">
<img src="https://user-images.githubusercontent.com/70312248/159523379-8ae58c66-dec1-4064-a635-1fefafd94951.png" width="1000" height="800"/> 
<br><br>
</div>
</details>

#### 4. GPIO
<details>
<summary>📌</summary><br> 
<div markdown="1">
<img src="https://user-images.githubusercontent.com/70312248/159959285-bc493d3a-595a-4388-87f2-ba588e34d70d.png" width="1000" height="300"/> 
<br><br>
</div>
</details>

#### 5. DMA
<details>
<summary>📌</summary><br>  
<div markdown="1">
  • <b> USART1,USART2 DMA Request Setting </b> <br>
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-&nbsp;[USART1_RX, USART2_RX]&nbsp;:&nbsp;&nbsp;Mode → <b>Circular</b> <br>
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-&nbsp;[USART1_TX, USART2_TX]&nbsp;:&nbsp;&nbsp;Mode → <b>Normal</b> (All Default) <br>
  <br>
<img src="https://user-images.githubusercontent.com/70312248/156927328-636cea39-5139-4d75-a712-6036b3b737fb.png" width="1000" height="250"/> 
<br><br>
</div>
</details>


#### 6. NVIC
<details>
<summary>📌</summary><br>  
<div markdown="1">
<img src="https://user-images.githubusercontent.com/70312248/156927343-a8df82b3-ea2e-406c-b25b-9c5e10f65b24.png" width="1000" height="600"/> 
<br><br>
</div>
</details>



<br>


## How to use<br>
  테스트를 하기 위해서는 `stm32f103_fw_module → src → main.c` 에서 주석을 해제 또는 설정해야 합니다..

```C
#include "main.h"

int main(void)
{
	hwInit();
	apInit();

/* Choose  Test Function */

  	apBoardTest();
//	apUartTest();
//	apGpioTest();
//      apDFPlayerTest();
//	apNRF24L01RxTest();
//	apNRF24L01TxTest();
//      apCLCDTest();
//      apDotMatrixTest();

    return 0;
}
```


<br>


## Note<br>
### 1.
`clcd.h`와 `max7219.h`의  #define에서  0x00~0x0f 부분이 중복되어 오류가 발생합니다. 따라서  clcd와 dot matrix는  동시에 테스트할 수 없습니다. 양쪽(clcd & dot matrix)을 동시에 테스트하려면 max7219.h의 #define 0x00 ~0x0f 부분을 static const하게 선언하여 사용해야합니다.

An error occurs due to overlapping parts 0x00~0x0f in #define of `clcd.h` and `max7219.h`. Therefore, clcld and dot matrix cannot be tested at the same time.
To test both simultaneously (clcd & dot matrix), you must use the static const declaration of #define 0x00 ~ 0x0f (max7219.h).


### 2. 
프로젝트를 빌드할 때는 다음 경로에 있는 폴더를 빌드 및 디버그 항목에서 제외해야 합니다.<br>
When you build a project, you must **exclude** folders in the following paths from the build and debug entries: <br>
* **`stm32f411ceu6_fw_module → src → lib → Core`**
#### **How to exclude**
<details>
  <summary>:pushpin:</summary><br>
<div markdown="1">
  • Click <b>Core</b> folder and proceed with the following steps.   <br><br>
  <img src="https://user-images.githubusercontent.com/70312248/166666504-b65bb2b8-3d73-4d9b-8022-54a35c26f02e.png" width="440" height="550"/> 
 　　　
<img src="https://user-images.githubusercontent.com/70312248/166665088-0c16c066-1b22-406a-b485-4e3af1d21884.png" width="310" height="450"/> 
<br><br><br><br>
  
• The results are as follows. <br><br>
<img src="https://user-images.githubusercontent.com/70312248/166665097-75e0de2d-5408-4d7c-8544-dc5f011807af.png" width="100" height="30"/> 
<br><br><br>
  
</div>		
</details>

<br>




## Test Pic<br>
<details>
<summary>🚩</summary><br>
 
<summary>DFplayer Mini</summary>
<div markdown="1">
<br>
<img src="https://user-images.githubusercontent.com/70312248/160285371-4d8a28d3-08db-4071-aee9-eca2b0d1d6bc.png" width="300" height="300"/> 
</div>
<br>

<summary>NRF24L01</summary>
<div markdown="1">
<br>
<img src="https://user-images.githubusercontent.com/70312248/160285791-28219e26-f6f1-47f3-bae3-bc669fdde01b.png" width="500" height="300"/> 
</div>
<br>

<summary>1602 CLCD With I2C</summary>
<div markdown="1">
<br>
<img src="https://user-images.githubusercontent.com/70312248/160285911-ba6bbfc3-5d7b-485e-af2a-4baaee6952e5.png" width="500" height="300"/> 
</div>
<br>

<summary>8*8 Dot Matrix With MAX7219</summary>
<div markdown="1">
<br>
<img src="https://user-images.githubusercontent.com/70312248/160285962-3274f4ed-1688-4f78-b46d-914b1daee9b0.png" width="400" height="300"/> 
</div>
</details>

<br>



## Refer to<br>
**8x8 Dot Matrix**  : https://github.com/eziya/STM32_HAL_MAX7219_8x8_MATRIX
