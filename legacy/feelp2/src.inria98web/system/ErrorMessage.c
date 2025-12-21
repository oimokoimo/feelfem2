/*
 * FEEL system Prototype Version 2
 * 
 * File     ErrorMessage.c
 * Made     1992/09/21
 * Modified 
 * Version  0.0
 *
 * Purpose: Print error message
 *
 */

/*[FEM_dx,FEM_dy,FEM_grad]
 *
 */
void NotFEMvariableError( var_name, module_name)
     char *var_name;
     char *module_name;
{
    char buf[256];

    sprintf(buf,"%s is not FEM variable(%s).",var_name,module_name);
    SystemError(buf);

    return;
}

void NotDefinedVariableError( var_name , module_name)
     char *var_name;
     char *module_name;
{
    char buf[256];
    
    sprintf(buf,"%s is not defined(%s).",var_name,module_name);
    SystemError(buf);

    return;
}

void NotDefinedRegionError( region_name , module_name )
     char *region_name;
     char *module_name;
{
    char buf[256];
    
    sprintf(buf,"region %s is not defined(%s).",region_name,module_name);
    SystemError(buf);
    
    return;
}


void ConstantVariableSpecifiedError( var_name, module_name )
     char *var_name;
     char *module_name;
{
    char buf[256];
    sprintf(buf,"%s is a constant variable(%s).",var_name,module_name);
    SystemError(buf);

    return;
}

/*
 *[Set_SOLVE_ncond_l]
 */
void NotAcceptableVariableError( var_name , module_name )
     char *var_name;
     char *module_name;
{
    char buf[256];
    
    sprintf(buf,"%s is not accepatable here(%s).",var_name,module_name);
    SystemError(buf);

    return;
}

void NotDefinedLineError( edge_name, module_name)
     char *edge_name;
     char *module_name;
{
    char buf[256];
    
    sprintf(buf,"%s is not defined edge(%s).",edge_name,module_name);
    SystemError(buf);

    return;
}

void LetScalarVariableError( var_name )
     char *var_name;
{
    char buf[256];
    
    sprintf(buf,"fem variable %s appeared in scalar let sentence.",var_name);
    SystemError(buf);

    return;
}

void LetScalarKeywordError( term )
     char *term;
{
    char buf[256];
    sprintf(buf,"FEEL keyword %s is in scalar let sentence.",term);
    SystemError(buf);

    return;
}

void LetScalarTermAbort( term )
     char *term;
{
    char buf[256];
    sprintf(buf,"Scalar let statement detects error term=%s.",term);
    SystemAbort(buf);
}

void LetFEMTermAbort( term )
     char *term;
{
    char buf[256];
    sprintf(buf,"FEM let statement detects error term=%s.",term);
    SystemAbort(buf);
}

void LetFEMkeywordError( term )
     char *term;
{
    char buf[256];
    sprintf(buf,"FEEL keyword %s is not allowd in fem-let sentence.",term);
    SystemError(buf);
}

void OpenFileToReadAbort( name )
     char *name;
{
    char buf[256];
    sprintf(buf,"Open %s to read failed.",name);
    SystemAbort(buf);
}

void OpenFileToWriteAbort( name )
     char *name;
{
    char buf[256];
    sprintf(buf,"Open %s to write failed.",name);
    SystemAbort(buf);
}

void OpenPipeToReadAbort( cmd )
     char *cmd;
{
    char buf[256];
    sprintf(buf,"Open command pipe '%s' failed.",cmd);
    SystemAbort(buf);
}

void InternalBlockNoAbort( no )
     int no;
{
    char buf[256];
    sprintf(buf,"Not existing block no.%d (internal error)",no);
    SystemAbort(buf);
}

void InternalTooManyLabelsAbort()
{
    SystemAbort("Too many labels(internal error in line no getting)");
}

void InternalTooManyFEMLETsAbort()
{
    SystemAbort("Too many fem lets(internal error in line no getting)");
}


void GotoLabelNotDefinedError( label , yylineno )
     char *label;
     int yylineno;
{
    char buf[256];
    sprintf(buf,"goto label %s is not defined(%d).",label,yylineno);
    SystemError(buf);
    return;
}

    
void TooManyPutRegionDataError()
{
    char buf[256];
    SystemError("Too many region data(Internal Error)");
    return;
}

void InternalError( module_name )
     char *module_name;
{
    char buf[256];

    sprintf(buf,"Internal Error (%s)",module_name);
    SystemAbort( buf );
}

	    
/*---------------*/
void StoreMakefileWarning( s )
     char *s;
{
     SystemWarning( s );
     return;
}

