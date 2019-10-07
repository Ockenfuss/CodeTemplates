#Makefile




INCDIR=includelib/
OBJDIR=lib

srcfiles=$(wildcard *.c)
objfiles=$(srcfiles:.c=.o)
prgmfiles=$(srcfiles:.c=)


all:$(prgmfiles)

#If the prerequesites are used in the recipe, make knows that they have to be build first!
#But what if they are build by another makefile in another directory?
#Solution: Create a new rule, which calls that makefile in the subdirectory and let it do the work!
Example: Example.o $(OBJDIR)/ascii.o $(OBJDIR)/cinput.o $(OBJDIR)/ini.o
	gcc -o Example $^

Test: Test.o
	gcc -o Test Test.o

Test.o: Test.c
	gcc -c Test.c


#If one of the c files was changed, we call the sub-make to update the object files
$(OBJDIR)/%.o: $(OBJDIR)/%.c
	$(MAKE) -C lib/


# %.o:%.c
# 	gcc -c $< -iquote $(INCDIR)