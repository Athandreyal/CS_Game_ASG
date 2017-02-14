#include <osbind.h>
#include "raster.h"

int main()
{
	void *base = Physbase();
	UINT8 tst_btmp[] = 
	
	plot_pix(base,320,200);
	p_v_ln(base, 330,200,8);
	p_h_ln(base,320,212,8);
	p_btmp_8(base, 320,100,tst_btmp);
	clr_scrn(base)
	return 0;
}
