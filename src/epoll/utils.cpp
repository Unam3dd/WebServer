#include "epoll.hpp"

/*********************************************************************
*
* @brief    Get Epoll File descriptor
*
* @param    void
*
* @return   Epoll File descriptor
*
*********************************************************************/
int	Epoll::Getfd(void) const
{
	return (this->_efd);
}
