//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Ping()
{
unsigned char signal = 0;
    switch(ping_state)
    {
        case PInit:
		signal++;
		if(signal >= 10){
			ping_state = active;
		}
		else{
			ping_state = PInit;
		} 
            break;
	case active:
		signal = 0;
		ping_state = PInit;
		break;
        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
		ping_data = 0x00;
            break;
	case active:
		ping_data = 0x01;
		break;
        default:
            break;
    }
}
