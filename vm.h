// #include <unistd.h>
// #include "global.h"
#include "vmop.h"


void eval()
{
  long op, *tmp;
  pc = orig;
  while(1)
  {
    op = *pc;++pc;
    // printf("%p\n",op);
    // Register Movement
    // if (op == IMM) {ax=*pc++;}
    // else if (op == LI) {ax = *(long *)(ax);}
    // else if (op == LC) {ax = *(char *)(ax);}
    // else if (op == SI) {ax = *(long *)*sp++ = ax;}
    // else if (op == SC) {ax = *(char *)*sp++ = ax;}

    // Control Flow
    // else if (op == PUSH) {*--sp = ax;}
     if (op == JMP) {pc = (long *)(*pc);}
    else if (op == JZ) {pc = (ax.data!=0) ? (long*)(pc+1) : (long*)*((long*)pc);}
    else if (op == JNZ) {pc = (ax.data!=0) ? (long*)*((long*)pc) : (long*)(pc+1) ;}
    //
    // // Function Call Releated
    else if (op == CALL) {op_call();}
    // else if (op == ENT) {*(--sp)=(long)bp; bp=sp; sp-=*pc++;}
    // else if (op == ADJ) {sp+=*pc++;}
    // else if (op == LEV) {bp=sp; bp=(long *)*sp++; pc=(long *)*sp++;}
    // else if (op == LEA) {ax=(long)*(bp+*pc++);}
    else if (op == RET) {op_ret();}

    // Math
    else if (op == OR){ op_or(); }
    else if (op == XOR){ op_xor(); }
    else if (op == AND){ op_and(); }
    else if (op == EQ){ op_equal(); }
    else if (op == NE){ op_notequal(); }
    else if (op == LT){ op_lt(); }
    else if (op == LE){ op_le(); }
    else if (op == GT){ op_gt(); }
    else if (op == GE){ op_ge(); }
    else if (op == SHL){ op_shl(); }
    else if (op == SHR){ op_shr(); }
    else if (op == ADD){ op_add(); }
    else if (op == SUB){ op_sub(); }
    else if (op == MUL){ op_mul(); }
    else if (op == DIV){ op_div(); }
    else if (op == MOD){ op_mod(); }
    else if (op == GETELEM){ op_getelem(); }
    else if (op == SETELEM){ op_setelem(); }
    else if (op == ADDELEM){ op_addelem(); }
    //
    // // Built-in's OR syscalls
    else if (op == EXIT)//{return;}
    {
      if (opreq)
      {
        printf("\x1B[31mOut[%ld]:\x1B[37m ",line);
        view(&ax);
        puts("");
      }
      return;
    }
    // else if (op == OPEN) {ax = open((char*)sp[1],sp[0]);}
    // else if (op == READ) {ax = read(sp[2],(char*)sp[1],*sp);}
    // else if (op == CLOSE) {ax = close(*sp);}
    // else if (op == PRTF) {tmp = sp+pc[1]; printf((char*)tmp[-1],tmp[-2],tmp[-3],tmp[-4],tmp[-5]);}
    // else if (op == MALC) {ax = (long)malloc(*sp);}
    // else if (op == MSET) {ax = (long)memset((char*)sp[2], sp[1], sp[0]);}
    // else if (op == MCMP) {ax = memcmp((char*)sp[2], (char*)sp[1], *sp);}
    // else {printf("Unknown Instruction: %ld", op);}

    else if (op == IMM)
    {
      ax.type = (long)*pc++;
      ax.data= (long)*pc++;
    }
    else if (op == PUSH)
    {
      --sp;
      val* tmp = sp;
      tmp->type = ax.type;
      tmp->data= ax.data;
    }
    else if (op == GET)
    {
      if (ax.type != PTR)
      {
        puts("ERROR: Invalid Access!");
        exit(-1);
      }
      st* temp = (st*)ax.data;
      ax.type = temp->value->type;
      ax.data = temp->value->data;
    }
    else if (op == SET)
    {
      val* temp = (val*)sp;
      if (temp->type != PTR)
      {
        puts("ERROR: Invalid Access!");
        exit(-1);
      }
      st* target = (st*)temp->data;
      sp++;
      target->value->type = ax.type;
      target->value->data = ax.data;
    }

  }
  return;
}
