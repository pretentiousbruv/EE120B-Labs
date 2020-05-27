//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Transmit()
{
    switch(transmit_state)
    {
        case TInit:
		transmit_state = ping;
            break;
	case ping:
		transmit_state = detect;
		break;
	case detect:
		transmit_state = max_amp;
		break;
	case max_amp:
		transmit_state = zero_cross;
		break;
	case zero_cross;
		transmit_state = Tinit;
		break;
	default:
            transmit_state = TInit;
            break;
    }
    switch(transmit_state)
    {
        case TInit:
            break;
	case ping:
		PORTB = PORTB | ping_data;
		break;
	case detect:
		PORTB = PORTB | detected;
		break;
	case max_amp:
		PORTB = PORTB | max;
		break;
	case zero_cross:
		PORTB = PORTB | cross;
		break;
        default:
            break;
    }

}
