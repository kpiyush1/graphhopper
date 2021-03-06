
#include "bridge.h"

Bridge::Bridge(LabelType labelType, double c) {
  this -> c = c;
  switch(labelType) {
  case Discrete:
    _fCompute = &Bridge::computeDiscrete;
    break;
  case Vector:
    _fCompute = &Bridge::computeVector;
    break;
  }
}

double Bridge::compute(Node *v1, Node *v2) {
  return (this->*_fCompute)(v1, v2);
}

double Bridge::computeVector(Node *v1, Node *v2) {
  int maxLength = std::max((int) v1 -> vLabel.size(), (int) v2 -> vLabel.size());
  if (v1 -> vLabel.size() < v2 -> vLabel.size()) {
    for(int i = (int) v1 -> vLabel.size() - 1; i < (int) v2 -> vLabel.size(); i++) {
      v1 -> vLabel.push_back(0);
    }
  } else if(v1 -> vLabel.size() > v2 -> vLabel.size()) {
    for(int i = (int) v2 -> vLabel.size() - 1; i < (int) v1 -> vLabel.size(); i++) {
      v2 -> vLabel.push_back(0);
    }
  }
  vector<double> xny(maxLength);
  for(int i = 0; i < maxLength; i++) {
    xny[i] = v1 -> vLabel[i] - v2 -> vLabel[i];
  }
  double normxny = 0;
  for(int i = 0; i <  maxLength; i++) {
    normxny += xny[i] * xny[i];
  }
  normxny = sqrt(normxny);
  return std::max(0.0, c - std::abs(normxny));
}

double Bridge::computeDiscrete(Node *v1, Node *v2) {
  return std::max(0.0, c - std::abs(v1 -> dLabel - v2 -> dLabel));
}
