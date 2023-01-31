/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btekinli <btekinli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:14:23 by btekinli          #+#    #+#             */
/*   Updated: 2022/10/13 15:23:54 by btekinli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_ms;

/*
"init_app" adlı fonksiyon, uygulamanın başlatılması sırasında gerekli olan ilk adımların yapılmasını sağlar. Bu fonksiyon, bellekte errno değişkeni için bir boşluk açar, "g_ms.paths" global değişkenini NULL'a ayarlar, "g_ms.parent_pid" global değişkenini çalışan programın PID'sini alır, "set_env" fonksiyonunu çağırarak ortam değişkenlerini ayarlar ve "set_paths" fonksiyonunu çağırarak yolları ayarlar.
*/

void	init_app(char **env)
{
	errno = 0;
	g_ms.paths = NULL;
	g_ms.parent_pid = getpid();
	set_env(env);
	set_paths();
}

/*"init_shell" fonksiyonu, bir kullanıcı tarafından girilen komut satırının tokenize edilmesi, lexer tarafından analiz edilmesi ve sonuçta çalıştırılmasını sağlar. Bu fonksiyon, token dizilerini ve işlem dizilerini g_ms yapısı içerisinde tanımlar ve başlatır, ardından da çalıştırılması tamamlanan komut satırından boşalmasını sağlar.*/

void	init_shell(char *input)
{
	g_ms.token = NULL;
	g_ms.process = NULL;
	g_ms.process_count = 0;
	tokenize(input);
	if (!lexer())
		return ;
	start_cmd();
	free_process();
}

/*
Bu fonksiyon, işletim sistemi tarafından SIGINT sinyali olarak adlandırılan bir sinyali ele alır ve bu sinyal, kullanıcının Ctrl + C tuşlarına basması durumunda tetiklenir. Fonksiyon, ekranda bir satır altına inmek için TIOCSTI ioctl çağrısı yapar ve sonra g_ms.ignore değişkenini TRUE olarak ayarlar. Bu, giriş ekranının "minishell_>" olarak tanımlanmış olan başlığını tekrar yazdırmasını ve kullanıcının tekrar komut girmesine izin vermesini sağlar.
*/

void	ctrl_c(int sig)
{
	(void)sig;
	g_ms.ignore = TRUE;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}

/*
Bu fonksiyon, kullanıcı tarafından girilen verinin boş olup olmadığını kontrol eder. Eğer veri boşsa, ekrana "exit" yazdırır ve programı sonlandırır.
*/

void	ctrl_d(char *input)
{
	if (!input)
	{
		printf("exit\n");
		exit(errno);
	}
}

/*
Başlamadan önce uygulamayı başlatmak için `init_app` fonksiyonunu çağırır ve daha sonra sonsuz bir döngü içinde `readline` fonksiyonunu kullanarak kullanıcıdan girdi okur. Okunan girdi, `init_shell` fonksiyonu aracılığıyla işlenir ve işlenen girdi `add_history` fonksiyonu aracılığıyla geçmişe eklenir. Döngü sonunda, girdi bellekten boşaltılır ve döngü tekrar başlar.
*/

int	main(int ac, char **av, char **env)
{
	char	*input;

	init_app(env);
	while (ac && av)
	{
		g_ms.ignore = FALSE;
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		write(1, "\033[32m", 5);
		input = readline("minishell_> ");
		write(1, "\033[0m", 4);
		ctrl_d(input);
		if (g_ms.ignore)
		{
			free(input);
			input = malloc(1);
		}
		if (*input)
		{
			init_shell(input);
			add_history(input);
		}
		free(input);
	}
	exit(errno);
}
