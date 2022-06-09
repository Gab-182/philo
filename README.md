# Philosophers
Apply the basics of threading a process.  Creating threads and discover mutexes.
----------------------------------------------------------------------------------
### The specific rules for the mandatory part are:
1. Each philosopher should be a thread.
2. There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on 
their left side and a fork on their right side.  If there is only one philosopher, there should be only one fork on the table.
3. To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them

# Resources

### General:
> https://codecharms.me/posts/operating-system-the-dining-philosophers-problem
> https://pages.mtu.edu/~shene/NSF-3/e-Book/MUTEX/TM-example-philos-1.html#:~:text=To%20address%20this%20problem%2C%20we,chopsticks)%2C%20and%20can%20eat.
-------------------------------------------------------------------------------------------
### Threads:
> https://man7.org/linux/man-pages/man7/pthreads.7.html
> 
> https://riptutorial.com/c/example/2622/data-race#:~:text=The%20execution%20of%20a%20program,race%20results%20in%20undefined%20behavior.
> 
> https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
> 
> https://www.youtube.com/watch?v=HDohXvS6UIk
> 
> https://www.youtube.com/watch?v=d9s_d28yJq0
> 
> https://www.youtube.com/watch?v=xoXzp4B8aQk
-------------------------------------------------------------------------------------------
### Mutexes:
> https://docs.oracle.com/cd/E19455-01/806-5257/sync-12/index.html
> 
> https://www.delftstack.com/howto/c/mutex-in-c/
> 
> https://www.youtube.com/watch?v=oq29KUy29iQ
-------------------------------------------------------------------------------------------
### Helgrined and Data races
> http://www.it.uc3m.es/pbasanta/asng/course_notes/helgrind_tool_en.html
> 
> https://valgrind.org/docs/manual/hg-manual.html
> 
>  https://riptutorial.com/c/example/2622/data-race#:~:text=The%20execution%20of%20a%20program,race%20results%20in%20undefined%20behavior.
