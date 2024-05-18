/*******************************************************************/
/*  Simple program using argp to parse the command line arguments  */
/*  Command Syntax: ./argp_simple -g m/f -a 26 Tom                 */
/*******************************************************************/

# include <stdio.h>
# include <argp.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>

/* Externs needed by argp */
const char *argp_program_version      = "argp example version 1.0" ; // Program version
const char *argp_program_bug_address  = "email@domain.com" ; // Developer email

/* File local properties */
static char doc[]                     = "Program to hold commands" ; // Program description
static char args_doc[]                = "<name>" ; // Non-Option arguments syntax, appended to "Usage: [OPTION...]" help message

static struct   argp_option options[] = { // Options expected in the command line
	{ "gender",  'g',  "<m/f>",     0,   "gender of the person"}, // Long Option, Key/Short Option, Argument Name, Flags, Document]  
	{ "age",     'a',  "<age>",     0,   "age of the person"},
	{ 0 } 
} ;

/* Custom struct to keep track of arguments, an instance of this is passed to argp_parse(), which sends it as a parameter state->input to parser function */
struct arguments {
	char        name[101] ; // Name value from command line
	char        gender ; // Gender value from command line
	unsigned    age ; // Age value from command line
	bool        gender_present ; // Whether gender option present 
	bool        age_present ; // Whether age option present
} ;

/* Check if input string is number */
bool is_number(char *argument) {
	for(char *chptr = argument; *chptr; ++chptr) {
		if (*chptr < '0' || *chptr > '9') {
			return false ;
		}
	}

	return true ;
}

/* Check if input string is alphabet/space, trim extra space, copy to destination */
bool check_space_alpha_trim_copy(char *dest, char *src, int limit) { // Checks only the first 'limit' number of characters that are copied
	unsigned char_count = 0 ;

	for (char *from = src; *from && char_count != limit; ++from) {
		if (isalpha(*from)) {
			*(dest + char_count++) = *from ;
		} else if (*from != ' ') {
			*dest = '\0' ;
			return false ;
		} else if (char_count > 0 && *(dest + char_count - 1) != ' ') {
			*(dest + char_count++) = ' ' ;
		}
	}

	if (char_count > 0 && *(dest + char_count - 1) == ' ') {
		--char_count ;
	}

	*(dest + char_count) = '\0' ;

	return char_count > 0 ? true : false ;
}

/* Parser function, called by argp_parse for each argument */
static error_t parser(int key, char *argument, struct argp_state *state) { // Key/Short Option, Argument value, State containing arguments instance
	struct arguments *arguments = state->input ;

	switch(key) {
		case 'g': // Option argument - gender
			if (strnlen(argument, 2) != 1) {
				argp_usage(state) ;
			}

			char gender = tolower(*argument) ;

			if (gender != 'm' && gender != 'f') {
				argp_usage(state) ;
			}

			arguments->gender = gender ;
			arguments->gender_present = true ;

			break ;

		case 'a': // Option argument - age
			if (!is_number(argument)) {
				argp_usage(state) ;
			}

			unsigned long value = strtoul(argument, NULL, 10) ;

			if (value > 130) {
				argp_usage(state) ;
			}
		
			arguments->age = value ;
			arguments->age_present = true ;

			break ;

		case ARGP_KEY_ARG: // Non-Option argument - name
			if (state->arg_num > 0 || !check_space_alpha_trim_copy(arguments->name, argument, 100)) {
				argp_usage(state) ;
			}

			break;

		case ARGP_KEY_END:
			if (state->arg_num < 1 || !arguments->gender_present || !arguments->age_present) {
				argp_usage(state) ;
			}

			break ;

		default: 
			return ARGP_ERR_UNKNOWN ;
	}

	return 0 ;
}

int main(int argc, char **argv) {
	static struct argp argp = {options, parser, args_doc, doc} ;
	static struct arguments arguments ; 

	if (argp_parse(&argp, argc, argv, 0, NULL, &arguments) == 0) { // argp *argp, int argc, char **argv, int flags, int *arg_index, void *input
		printf("Name = (%s) Gender = (%s) Age = (%u)\n", arguments.name, arguments.gender == 'm' ? "male" : "female", arguments.age) ;
	}

	return 0 ;
}
