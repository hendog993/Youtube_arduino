//uint16_t rotCounter;
//uint32_t rotVector;
// 
//void rotISR()
//{
//    rotVector = ( rotVector << 2u ) & 0xCu;
//    rotVector |= ( digitalRead(2) ) ? 2: 0;
//    rotVector |= ( digitalRead(3) ) ? 1: 0;
//    //Serial.println(rotVector);
//    switch ( rotVector )
//    {
//    case 8:
//        rotCounter++;
//        break;
//    case 4:
//        rotCounter--;
//        break;
//    }
//}
