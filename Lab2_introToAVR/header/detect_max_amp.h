//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
unsigned char temp = 0x00;
unsigned char compare = 0x00;
temp = ~PINA;
temp = temp & 0xF8;
compare = PORTB;
compare = PORTB & 0xF8;
/* complete the state machine. */

void Detect_Max_Amp()
{
    switch(detect_max_amp_state)
    {
        case DMAInit:
		if(temp > compare){
			detect_max_amp_state = new_max_amp;
		}
		else{
			detect_max_amp_state = same_amp;
		}
            break;
	case new_max_amp:
		detect_max_amp_state = DMAInit;
		break;
        case same_amp:
		detect_max_amp_state = DMAInit;
		break;
        default:
            break;
    }
    switch(detect_max_amp_state)
    {
        case DMAInit:
            break;
	case new_max_amp:
		max = max | temp;
		break;
	case same_amp:
		max;
		break;
        default:
            break;
    }
}
