//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
unsigned char motion = 0x00;
unsigned char counter = 0;
motion = ~PINA & 0xF8;

/*complete the state machine*/

void Detect_EQ()
{
    switch(detect_eq_state)
    {
        case DEQInit:
		if(motion == 0x00){
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
		if(motion > 0x00){
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
