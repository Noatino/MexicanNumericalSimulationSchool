#include "defs.h"
#include "fdefs.h"

void
view_mag(job)
    char *job;
{
    char command[MAXCOMM] ;
    char type[MAXCOMM] ;
    char plot_type[MAXCOMM] ;
    char clip_type[MAXCOMM] ;
    double low ;
    double high ;
    int i ;

    if (boxes_loaded[0]) {
	if((i = sscanf(job,"%s %s %lf %lf %s %s",command,type,&low,&high,
		plot_type,clip_type)) >= 5) {
	    if(i == 6){
	        if(strcmp(clip_type,"clip") == 0 ||
			strcmp(clip_type,"c") == 0 ||
			strcmp(clip_type,"clipboth") == 0 ||
			strcmp(clip_type,"cb") == 0 ){
		    clip_flag = BCLIP ;
		}
	        else if(strcmp(clip_type,"clipup") == 0 ||
			strcmp(clip_type,"cup") == 0 ){
		    clip_flag = UPCLIP ;
		}
	        else if(strcmp(clip_type,"cliplo") == 0 ||
			strcmp(clip_type,"clo") == 0 ){
		    clip_flag = LOCLIP ;
		}
		else{
		    printf("<sorry, %s is not a proper option, %s>\n",
			    clip_type,title) ;
		    return ;
		}
	    }
	    else{
		clip_flag = NOCLIP ;
	    }
	    if(!magnitude_plot) {
		magnitude_plot = YES ;
		potential_plot = NO ;
		array_plot = NO;
		radial_plot = NO ;
		gas_plot = NO ;
		star_plot = NO ;
		load_color_table() ;
	    }
	    color_slope = 124.0 / (high - low) ;
	    color_offset = 2.0 - color_slope * low ;
	    if ( strcmp(type,"gas") == 0 ) {
		color_type = GAS ;
                log_type = LIN ;
	    }
	    else if ( strcmp(type,"dark") == 0 ) {
		color_type = DARK ;
                log_type = LIN ;
	    }
	    else if ( strcmp(type,"star") == 0 ) {
		color_type = STAR ;
                log_type = LIN ;
	    }
	    else if ( strcmp(type,"all") == 0 ) {
		color_type = ALL ;
                log_type = LIN ;
	    }
	    else if ( strcmp(type,"loggas") == 0 || strcmp(type,"lgas") == 0){
		color_type = GAS ;
                log_type = LOG ;
	    }
	    else if ( strcmp(type,"logdark") == 0 || strcmp(type,"ldark") == 0){
		color_type = DARK ;
                log_type = LOG ;
	    }
	    else if ( strcmp(type,"logstar") == 0 || strcmp(type,"lstar") == 0){
		color_type = STAR ;
                log_type = LOG ;
	    }
	    else if ( strcmp(type,"logall") == 0 || strcmp(type,"lall") == 0){
		color_type = ALL ;
                log_type = LOG ;
	    }
	    else {
		printf("<%s is an unknown particle type, %s>\n",type,title) ;
		return ;
	    }
	    if ( strcmp(plot_type,"velocity") == 0 ||
		    strcmp(plot_type,"vel") == 0 ) {
		vector_plot_type = VELOCITY ;
	    }
	    else if ( strcmp(plot_type,"vector") == 0 ||
                    strcmp(plot_type,"vec") == 0 ) {
		if(vector_size == 0){
		    printf("<sorry, no vector is loaded, %s>\n", title) ;
		    return ;
		}
		vector_plot_type = VECTOR ;
	    }
	    else {
		printf("<%s is an unknown plot_type, %s>\n",plot_type,title) ;
		return ;
	    }
	    project() ;
	    current_color = NO;
	    magnitude_color() ;
	    plot_sub(job) ;
	}
	else {
	    input_error(command) ;
	}
    }
    else {
	printf("<sorry, no boxes are loaded, %s>\n",title) ;
    }
}
