// Autogenerated by convert_protofile.py.
// Do not edit this file directly.
// The template for this file is located at:
// ../../../../../../../../templates/AstSubclass.java
package com.rethinkdb.ast.gen;

import com.rethinkdb.ast.helper.Arguments;
import com.rethinkdb.ast.helper.OptArgs;
import com.rethinkdb.ast.RqlAst;
import com.rethinkdb.proto.TermType;
import java.util.*;



public class November extends RqlQuery {


    public November(java.lang.Object arg) {
        this(new Arguments(arg), null);
    }
    public November(Arguments args, OptArgs optargs) {
        this(null, args, optargs);
    }
    public November(RqlAst prev, Arguments args, OptArgs optargs) {
        this(prev, TermType.NOVEMBER, args, optargs);
    }
    protected November(RqlAst previous, TermType termType, Arguments args, OptArgs optargs){
        super(previous, termType, args, optargs);
    }


    /* Static factories */
    public static November fromArgs(Object... args){
        return new November(new Arguments(args), null);
    }


}