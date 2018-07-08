#ifndef HANOI_TOWER_HPP
#define HANOI_TOWER_HPP

#include <atomic>
#include <future>
#include <mutex>

#include <clever/Field.hpp>





// data
struct HanoiTowerData
{
	int *first;
	int *second;
	int *third;

	size_t height;



	inline int const *get(int what) const
	{
		switch(what)
		{
		case 0:
			return first;
		case 1:
			return second;
		case 2:
			return third;
		default:
			throw "invalid tower index";
		}
	}

	inline int *get(int what)
	{
		switch(what)
		{
		case 0:
			return first;
		case 1:
			return second;
		case 2:
			return third;
		default:
			throw "invalid tower index";
		}
	}
};





// the class
class HanoiTower
{
public:
	// creation and destroy
	HanoiTower(
		HanoiTowerData const &data =
			{ nullptr, nullptr, nullptr, 0u }
	);
	~HanoiTower();



	// core methods

	/*
	 * запускает алгоритм в отдельном потоке. Если
	 * алгоритм уже запущен, поведение неопределено
	 */
	HanoiTower &run(int from, int to);
	/*
	 * позволяет узнать, запущен ли поток
	 */
	bool isRun() const;

	/*
	 * останавливает/запускает алгоитм
	 */
	HanoiTower &pause(bool enable);
	/*
	 * позволяет понять, простаивает ли алгоритм
	 */
	bool pause() const;

	/*
	 * прерывает выполнение алгоритма, пауза сбрасывается
	 */
	HanoiTower &interrupt();
	/*
	 * ожидает завершения алгоритма, если стоит пауза, зависает.
	 * Используйте после вызова interrupt, чтобы гарантировать
	 * завершение потока
	 */
	HanoiTower &wait();

	/*
	 * отображает башни на поле, поле должно быть шириной
	 * не менее (1 + 2*(высота_башни-1))*3 + 2, 
	 * и высотой не менее высоты башни
	 */
	HanoiTower &reflect(clever::Field<int> &f);



	// data
	HanoiTower &setData(HanoiTowerData const &data);
	HanoiTower &releaseData();
	HanoiTowerData const &getData() const;



private:
	// class are not copyable
	HanoiTower(HanoiTower const &tocp);
	HanoiTower &operator=(HanoiTower const &tocp);

	// implement functions and procedures
	bool work_implement_(HanoiTowerData *d, int from, int to);
	void free_();



	// data members
	HanoiTowerData d_;
	std::mutex datamutex_;

	std::future<bool> future_;
	std::atomic_bool interrupt_;

	std::mutex pausemutex_;
	std::unique_lock<std::mutex> pauselock_;



};





#endif
