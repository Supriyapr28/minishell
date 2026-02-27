#include "../minishell.h"

static void	execute_child(const char *cmd_path, char **args, char **envp)
{
    execve(cmd_path, args, envp);
    perror("execve");
    exit(127);
}

// Execute command
void execute_command(char **args, char **envp)
{
    char *cmd_path;
    pid_t pid;
    int status;

    cmd_path = find_command(args[0], envp);
    if (!cmd_path)
    {
        printf("minishell: command not found: %s\n", args[0]);
        return ;
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(cmd_path);
        return ;
    }
    if (pid == 0)
        execute_child(cmd_path, args, envp);
    else
        waitpid(pid, &status, 0);
    free(cmd_path);
}
