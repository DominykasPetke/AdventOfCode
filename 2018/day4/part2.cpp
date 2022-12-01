#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <array>
#include <map>

struct entry
{
	int year, month, day, hour, minute;

	int id;
	bool asleep;
};

struct sleepTimes
{
	std::array<int, 60> sleepTime;

	sleepTimes()
	{
		sleepTime.fill(0);
	}

	sleepTimes(std::array<int, 60> const &in)
	{
		sleepTime = in;
	}
};

bool read(std::ifstream &in, entry &out)
{
	std::string line;
	if (std::getline(in, line))
	{
		line.erase(0, 1);
		out.year = std::stoi(line);

		line.erase(0, line.find('-') + 1);
		out.month = std::stoi(line);

		line.erase(0, line.find('-') + 1);
		out.day = std::stoi(line);

		line.erase(0, line.find(' ') + 1);
		out.hour = std::stoi(line);

		line.erase(0, line.find(':') + 1);
		out.minute = std::stoi(line);

		line.erase(0, line.find(' ') + 1);

		switch (line[0])
		{
		case 'w':
			out.asleep = false;
			out.id = -1;
			break;
		case 'f':
			out.asleep = true;
			out.id = -1;
			break;
		case 'G':
			line.erase(0, line.find('#') + 1);
			out.id = std::stoi(line);
			out.asleep = false;
		default:
			break;
		}

		return true;
	}

	return false;
}

int main()
{
	std::ifstream in("input");

	std::vector<entry> data;
	entry line;

	while (read(in, line))
		data.push_back(line);

	std::sort(data.begin(), data.end(), [](const entry &t, const entry &f) {
		if (t.year < f.year)
			return true;
		if (t.year > f.year)
			return false;

		if (t.month < f.month)
			return true;
		if (t.month > f.month)
			return false;

		if (t.day < f.day)
			return true;
		if (t.day > f.day)
			return false;

		if (t.hour < f.hour)
			return true;
		if (t.hour > f.hour)
			return false;

		if (t.minute < f.minute)
			return true;
		if (t.minute > f.minute)
			return false;

		return false;
	});

	std::map<int, sleepTimes> sleeps;

	int id = -1;
	int beganSleep = -1;

	for (int i = 0; i < data.size(); i++)
	{
		id = data[i].id == -1 ? id : data[i].id;

		if (data[i].asleep)
			beganSleep = data[i].minute;

		else if (beganSleep != -1 && !data[i].asleep)
		{
			for (int j = beganSleep; j < data[i].minute; j++)
				sleeps[id].sleepTime[j]++;

			beganSleep = -1;
		}
	}

	int max = -1;
	int min = -1;

	for (std::map<int, sleepTimes>::iterator it = sleeps.begin(); it != sleeps.end(); ++it)
		for (int i = 0; i < 60; i++)
			if (it->second.sleepTime[i] > max)
			{
				max = it->second.sleepTime[i];
				id = it->first;
				min = i;
			}

	std::cout << id * min << '\n';
	return 0;
}