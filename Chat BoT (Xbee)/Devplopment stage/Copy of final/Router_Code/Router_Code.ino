    #include <XBee.h>
    
    #include <SoftwareSerial.h>

    SoftwareSerial zigbeee(10,11);

    XBee xbee = XBee();

    static char payload[50];
    
    static char inByte[50];

    XBeeAddress64 addr64 = XBeeAddress64(0,0); //SH and SL address of receiver

    ZBTxRequest zbTx = ZBTxRequest(addr64, payload,sizeof(payload)); //instance for making the frame
    
    ZBTxStatusResponse txStatus = ZBTxStatusResponse(); //instance for getting the status

    XBeeResponse response = XBeeResponse();
    
    // create reusable response objects for responses we expect to handle
    
    ZBRxResponse rx = ZBRxResponse(); 

    FrameIdResponse f =  FrameIdResponse();
    
    uint8_t *a;
    
    char x[50];

    uint8_t add[7];
    
    void setup() {
      
      Serial.begin(115200);
      zigbeee.begin(9600);
      xbee.setSerial(zigbeee);
    
      delay(1000);
      
      }
    
     void loop() {
    
     boolean data_avai = false;
    
     int i = 0;
      
    //do{
     while(Serial.available() > 0){
      
      inByte[i] = Serial.read();  
      //Serial.print("i = ");Serial.print(i);
      //Serial.print("   ");
     // Serial.println(inByte[i],HEX);+
     delay(10);
      i++;
      
      }//}while(inByte[i]==13);
     if(inByte[0]=='t')
      {
       char ax = inByte[1];
       if(ax=='1'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fa);zbTx.setAddress64(addr64);Serial.print("you are now in conversation with xbee 1");}
       if(ax=='2'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fd);zbTx.setAddress64(addr64);Serial.print("you are now in conversation with xbee 2");}
       if(ax=='3'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x41565710);zbTx.setAddress64(addr64);Serial.print("you are now in conversation with xbee 3");}
       if(ax=='4'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x4156583E);zbTx.setAddress64(addr64);Serial.print("you are now in conversation with xbee 4");}
       if(ax=='5'){ XBeeAddress64 addr64 = XBeeAddress64(0xFFFFFFFF, 0xFFFFFFFF);zbTx.setAddress64(addr64);Serial.print("you are now in conversation with everyone");} 
       inByte[0]='d';
       
       }

      
     for(int j = 0; j < i; j++  )
       {  
          //Serial.print("j = " );Serial.print(j);
          //Serial.print(" ");
          payload[j] =  inByte[j];
          Serial.print(payload[j]);
          Serial.print("");
          
           if(j == i-1)
          {  
            data_avai = true;
            Serial.print("----------Message sent----");
            Serial.print(j);
            Serial.print("----");
            Serial.println();
            Serial.println();
            
        }}  
    
       /*  //data_avai = true;
     //payload[0] = ((pin1 << 2) | pin1) & 0x0F;
      //payload [1] = */
    if (data_avai == true) 
      {zbTx.setFrameId(5);
      xbee.send(zbTx);
      delay(100);}
    
    
     xbee.readPacket();
        
       if (xbee.getResponse().isAvailable()) {
          // got something
          
       if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
    
         xbee.getResponse().getZBRxResponse(rx);
         XBeeAddress64 return_address=rx.getRemoteAddress64();
         zbTx.setAddress64(return_address);
        /* int frame_id = f.getFrameId();
         Serial.println("Frame received Id = ");
         Serial.println(frame_id);
         got a zb rx packet*/
         //zbTx.getAddress64();
        //Serial.print(y);
        for (int j = 1; j < 9 ;j++)
        { 
          add[j]= return_address>>(64-(8*j));
          /*Serial.print(add[j],HEX);
          Serial.print(" ");*/
          }
        if(add[7]==86)
        {
         if(add[8]==250){Serial.print("Xbee 1:--");}
         if(add[8]==253){Serial.print("Xbee 2:--");} 
          
         }
        if(add[7]==87){Serial.print("Xbee 3:--");}
        if(add[7]==88){Serial.print("Xbee 4:--");} 
         
        
        a = rx.getData();     //getData() give an address...so put it in a pointer (here--> a <--is a pointer)
        
       for (int i = 0; i < 49 ; i++)
        {x[i]=a[i];               //get the first byte and put it in a variable
         Serial.print(x[i]);
         Serial.print("");
       if(i==48)
          {  
            
            Serial.print("----------- Message Received-----");
            Serial.println();
            
          }
        if(x[10]=='*'/*&&  x[16]=='&' && x[27]=='*'*/){
        
          //Serial.print("I got the request for  address");
          payload[0]=' ';
          zbTx.setFrameId(6);
          xbee.send(zbTx);
          delay(100);

        x[10]=' ';
        //x[16]=' ';
        //x[27]=' '; 
        }
         
       
          }  

        

    /*   for (int i = 0; i < 49 ; i++)
        {
          do {
             x[i]=a[i];               //get the first byte and put it in a variable
             Serial.print(x[i]);
             Serial.print("");
             
             }while(x[i]!= 0);
             
             }*/
        
    }}
    
    memset(payload,0,sizeof(payload));
    
    }
    
  
      

    /*void addressed_to()
    {
      
      Serial.print("Whom would you like to speak to?");
      Serial.print(" ");
      Serial.print("1 2 3 or 4");
      if(Serial.available()>0)
      {
       char ax = Serial.read();
       if(ax=='1'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fa);zbTx.setAddress64(addr64);}
       if(ax=='2'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fa);zbTx.setAddress64(addr64);}
       if(ax=='3'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fa);zbTx.setAddress64(addr64 );}
       if(ax=='4'){ XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415656fa);zbTx.setAddress64(addr64 );}
        }
      
      }memset(payload,0,sizeof(payload));*/
      

