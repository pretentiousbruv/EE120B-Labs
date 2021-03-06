//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i


/*complete the state machine*/

void Detect_EQ()
{
unsigned char motion_sense = 0x00;
unsigned char tempA = 0x00;
unsigned char counter = 0;
tempA = PINA;
tempA = ~tempA;
motion_sense = tempA & 0xF8;
    switch(detect_eq_state)
    {
        case DEQInit:
		if(motion_sense == 0x00){
			detect_eq_state = noquake;
		}
		else{
			detect_eq_state = quake;
		}
		break;
	case noquake:
		detect_eq_state = DEQInit;
		counter = 0;
		break;
	case quake:
		if(motion_sense > 0x00){
			detect_eq_state = quake;
			counter = 0;
		}
		else{
			counter++;
			if(counter >= 10){
				detect_eq_state = noquake;
			}
			detect_eq_state = quake;
		}//init variable(s) here.
            break;
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            break;
	case noquake:
		detected = detected & 0xFD;
		break;
	case quake:
		detected = detected | 0x02;
		break;
        default:
            break;
    }
}
