#ifndef DIRECTIVE_LINE_VALIDATIONS_H
#define DIRECTIVE_LINE_VALIDATIONS_H

#include "../front/helper_functions.h"
#include "../global.h"

void validate_and_update_directive(Line_obj *line_obj, char *line,
                                   Directive directive, Tokens_Obj *tokens_obj);

#endif