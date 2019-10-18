/**
 * @file ZoneReversal.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe contendo a análise de zonas de suporte e resistências
 * @version 0.1
 * @date 18-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef ZONEREVERSAL_HPP_
#define ZONEREVERSAL_HPP_

#include <vector>
#include "Chart.hpp"
#include "LinePrice.hpp"
#include "Zone.hpp"

class ZoneReversal {
 private:
  pip_t sizeOfZones;
  void setSizeOfZones(pip_t *);

 public:
  std::vector<Zone> zones;
  pip_t *getSizeOfZones(void);
  ZoneReversal(Chart *, pip_t, unsigned int);
  ZoneReversal(Chart *, pip_t, unsigned int, time_t, time_t);
  ~ZoneReversal(void);
};

#endif
