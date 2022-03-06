## Component<br>


|**Part Name**|**Image Link**|**Implementation**|
|:---:|:---:|:---:|
|DFplayer Mini|[📌](https://www.devicemart.co.kr/goods/view?no=1278727)|✓|
|NRF24L01|[📌](https://www.devicemart.co.kr/goods/view?no=12506373)|✓|

## Where's the file?<br>
<details>
<summary>📌</summary><br>
  
<summary>DFplayer Mini</summary>  
<div markdown="1">
<br>
-  &nbsp; stm32f103_fw_module → src → common → hw → include → dfplayer.h<br>
-  &nbsp; stm32f103_fw_module → src → hw → driver → dfplayer.c<br>
-  &nbsp; stm32f103_fw_module → src → ap → ap.c → void apDFPlayerTest(void){...}<br>
</div>
<br><br>
<summary>NRF24L01</summary>
<div markdown="1">
<br>
-  &nbsp; stm32f103_fw_module → src → common → hw → include → nrf24l01.h<br>
-  &nbsp; stm32f103_fw_module → src → hw → driver → nrf24l01.c<br>
-  &nbsp; stm32f103_fw_module → src → ap → ap.c → void apNRF24L01TxTest(void){...}<br>
-  &nbsp; stm32f103_fw_module → src → ap → ap.c → void apNRF24L01RxTest(void){...}<br> 
</div>
</details>


<br>

## Cube MX Setting<br>
### 1. Clock Configuration<br>
- Using HSE (High Speed External)<br><br>
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
<img src="https://user-images.githubusercontent.com/70312248/156926816-cd46825e-392c-4452-a740-515ae7ccae25.png" width="800" height="500"/> <br>
<br><br>

### 2. Pinout<br>
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
<img src="https://user-images.githubusercontent.com/70312248/156926532-3ba5d468-17f1-461b-b0ce-7aeeb1bdea12.png" width="600" height="500"/> <br>

<br><br>

### 3. Peripheral Configuration<br>
#### 3.1. UART
- UART2 is the same as USART1<br><br>
 <img src="https://user-images.githubusercontent.com/70312248/156927378-6c0fd54e-bd78-437c-8f49-289d4a90c563.png" width="1000" height="600"/> <br><br>

#### 3.2. SPI
 <img src="https://user-images.githubusercontent.com/70312248/156927368-b1cff53b-974c-42e0-80a3-1a3baf264159.png" width="1000" height="800"/> <br><br>

#### 3.3. DMA
- USART1, USART2 Mode is **RX Mode : Circular, Tx Mode : Normal** <br><br>
![image](https://user-images.githubusercontent.com/70312248/156927328-636cea39-5139-4d75-a712-6036b3b737fb.png)<br><br>

#### 3.4. NVIC
![image](https://user-images.githubusercontent.com/70312248/156927343-a8df82b3-ea2e-406c-b25b-9c5e10f65b24.png)<br><br>

#### 3.5. GPIO
![image](https://user-images.githubusercontent.com/70312248/156927391-3ef2943d-5674-498d-b65c-b1d23465881e.png)<br><br>

