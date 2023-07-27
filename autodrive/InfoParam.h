#pragma once

struct Point3D
{
  double m_x;
  double m_y;
  double m_z;

  Point3D():
  m_x(0.0),
  m_y(0.0),
  m_z(0.0)
  {

  }
};

struct ObstacleFrameInfo
{
  int32_t m_type;
  Point3D m_position;
  float m_theta;
  float m_length;
  float m_width;
  float m_height;
  ObstacleFrameInfo():
  m_type(0),
  m_theta(0.0),
  m_length(0.0),
  m_width(0.0),
  m_height(0.0)
  {
    
  }
};