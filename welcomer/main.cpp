/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noprysk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:50:14 by noprysk           #+#    #+#             */
/*   Updated: 2018/05/02 20:15:53 by noprysk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <vector>

#define BUFF_SIZE 124
#define MAX_NB_OF_CHAMPS 4

# define EOC "\033[0m"

# define BLACK "\e[30m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define MAGENTA "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"

# define BBLACK "\e[40"
# define BRED "\e[41m"
# define BGREEN "\e[42m"
# define BYELLOW "\e[43m"
# define BBLUE "\e[44m"
# define BMAGENTA "\e[45m"
# define BCYAN "\e[46m"
# define BWHITE "\e[47m"

# define BOLD "\033[1m"
# define ITAL "\033[3m"
# define UNDER "\033[4m"

static std::string read_output_of_command(std::string const& cmnd)
{
	std::stringstream ss;
	char buff[BUFF_SIZE];
	FILE*	ret = popen(cmnd.c_str(), "r");

	while (!feof(ret))
	{
		if (fgets(buff, BUFF_SIZE, ret))
			ss << buff;
	}

	pclose(ret);
	std::string str(ss.str());
	if (str.length() > 0)
		str.erase(str.end() - 1);
	return (str);
}

static void save_champions(std::vector<std::string>& champions)
{
	std::stringstream ss(read_output_of_command("sh display_champions.sh"));
	std::string str;
	while (ss){
		ss >> str;
		champions.push_back(&str[2]);
	}
}

static void print_champions(std::vector<std::string>& champions)
{
	int i = 0;
	for (auto& champ : champions)
		std::cout << BOLD << i++ << EOC << ". " << champ << std::endl;
}

static void choose_champions(std::string& compile_line)
{
	(void)compile_line;
	std::cout << BOLD << "Here are our champions:" << EOC << std::endl;
	std::vector<std::string> champions;
	save_champions(champions);
	print_champions(champions);
	int nb;
	int nb_of_champs = 0;
	char answer;
	while (nb_of_champs < MAX_NB_OF_CHAMPS){
		std::cout << BOLD << nb_of_champs << " champions selected by now." << EOC << std::endl;
		std::cout << "Whould you like to add a champion? (hit 'y' or 'n'): ";
		std::cin >> answer;
		if (answer == 'y'){
			std::cout << "Select number of champion: ";
			std::cin >> nb;
			if (nb >= 0 && nb < (int)champions.size()){
				compile_line += ' ';
				compile_line += champions[nb];
				std::cout << "Champion number " << nb << " selected." << std::endl;
				nb_of_champs++;
			}
			else
				std::cout << RED << "Out of range" << EOC << std::endl;
		}
		else if (answer == 'n')
			break ;
		else
			std::cout << RED << "Let's try again! I know you can make it!" << EOC << std::endl;
	}
}

static void enter_test_mode()
{
	std::cout << BOLD << "You are in test mode by far." << EOC << std::endl
	<< "If you would like to test assembler hit 'a'."  << std::endl
	<< "If you would like to test virtual machine hit 'v'."  << std::endl;
	char answer;
	while (1)
	{
		std::cout <<"Please hit 'a' or 'v': ";
		std::cin >> answer;
		if (answer == 'a')
		{
			system("sh check_asm.sh");
			std::cout << BOLD << "Are you finally satisfied?" << EOC << std::endl;
			break ;
		}
		else if (answer == 'v')
		{
			system("sh test_d.sh");
			system("test_v.sh");
			std::cout << BOLD << "Do you like what you see?" << EOC << std::endl;
			break ;
		}
	}
}

static void enter_basic_mode(std::string name)
{
	std::cout << BOLD << "You are in basic mode now " << CYAN << name << EOC << BOLD << '.' << EOC << std::endl
	<< EOC << "If you would like to run corewar without flags hit 'w'."  << std::endl
	<< "If you would like to run corewar with ncurses vizualization hit 'n'." << std::endl;
	char answer;
	std::string compile_line("./corewar");
	while (1)
	{
		std::cout << "Please hit 'w' or 'n': ";
		std::cin >> answer;
		if (answer == 'w')
			break ;
		else if (answer == 'n')
		{
			compile_line += " -nc";
			break ;
		}
	}
	std::cout << compile_line << std::endl;
	std::cout << BOLD << "Finally it's time to choose champions." << EOC << std::endl;
	choose_champions(compile_line);
	system(compile_line.c_str());
}

static void compile_cor_files()
{
	std::stringstream ss(read_output_of_command("sh display_s_files.sh"));
	std::string str;
	std::string command;
	while (ss){
		command += "./asm ";
		ss >> str;
		command += &str[2];
		system(command.c_str());
		command.clear();
	}
}

int main()
{
	system("clear");
	std::cout << BOLD << "Welcome to our wonderful corewar!" << EOC << std::endl;
	std::cout << "Please enter your name: ";
	std::string name;
	std::cin >> name;
	std::cout << "Hi " << CYAN << name << EOC << '!' << std::endl;
	char answer;
	std::cout << BOLD << "Would you like me compile the project for you? (hit y or n): " << EOC;
	std::cin >> answer;
	if (answer == 'y'){
		system("make");
		std::cout << GREEN << "Voilà!" << EOC << std::endl;
	}
	std::cout << BOLD << "Would you like me to create *.cor files out of *.s files? (hit y or n): "  << EOC;
	std::cin >> answer;
	if (answer == 'y'){
		compile_cor_files();
		std::cout << GREEN << "*.cor files are ready to serve!" << EOC << std::endl; 
	}
	std::cout << BOLD << "We have prepared a few modes for you." << EOC << std::endl
	<< "There are two types of modes: basic modes and test modes."  << std::endl
	<< "If you would like me to run one of basic modes hit 'b'." << std::endl
	<< "If you would like me to run one of test modes hit 't'."  << std::endl;
	while (1)
	{
		std::cout << "Please hit 'b' or 't': ";
		std::cin >> answer;
		if (answer == 'b')
			enter_basic_mode(name);
		else if (answer == 't')
			enter_test_mode();
		else
			continue ;
		break ;
	}
	std::cout << BOLD << "I hope to see you soon again " << CYAN
	<< name << EOC << BOLD  << "! Bye-bye!" << std::endl
	<< "It's time for me to delete myself. :(" << EOC << std::endl;
	return 0;
}
