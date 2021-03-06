// subscribe point cloud at current pose and transformation between current pose
// and the world frame;
// generate the point cloud map.

// Author: Chizhao Yang

#ifndef POINTCLOUDMAPBUILDER_H
#define POINTCLOUDMAPBUILDER_H

#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>

#include <nav_msgs/Odometry.h>
#include <sensor_msgs/PointCloud2.h>

#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>

typedef pcl::PointXYZI PointType;
class PointcloudMapBuilder{
public:
  PointcloudMapBuilder(ros::NodeHandle& nh);
  ~PointcloudMapBuilder() = default;

private:
  void pointcloudHandler(const sensor_msgs::PointCloud2ConstPtr& pointcloudMsg, const nav_msgs::Odometry::ConstPtr& odomTrans);

  void transfromCloudToMap();
  void publishMap();

  ros::NodeHandle _nh;

  ros::Publisher _pubGlobalMap;

  std::string _pointcloudTopic;
  std::string _globalMapTopic;
  std::string _odometryTopic;

  std::string _targetFrame;
  std::string _fileDirectory;

  pcl::PointCloud<PointType>::Ptr _cloudIn;
  pcl::PointCloud<PointType>::Ptr _globalMap;
  pcl::PointCloud<PointType>::Ptr _globalMapDS;

  pcl::VoxelGrid<PointType> _downSizeFilter;

  float _transfromCloudToMap[6];

  std_msgs::Header _cloudHeader;

};

#endif
