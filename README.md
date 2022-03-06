## Component<br>


|**Part Name**|**Image Link**|**Implementation**|
|:---:|:---:|:---:|
|DFplayer Mini|[📌](https://www.devicemart.co.kr/goods/view?no=1278727)|✓|
|NRF24L01|[📌](https://www.devicemart.co.kr/goods/view?no=12506373)|✓|
|MPU6050|[📌](https://www.devicemart.co.kr/goods/view?no=10825463)|note|

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


