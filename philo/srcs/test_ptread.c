#include "../../includes/philo.h"

void *do_something(void *arg)
{
	(void)arg;

	printf("do something\n");
	sleep(3);
	return (NULL);
}

int main(void)
{
	pthread_t thread;
	void *retval;

	// スレッドを作成
	if (pthread_create(&thread, NULL, do_something, NULL) != 0)
		// エラー処理
		return (0);
	// スレッドの終了方法
	// 1. スレッドが終了するまで待つ
	pthread_join(thread, &retval);
	// 2. スレッドを待たない
	pthread_detach(thread);
}