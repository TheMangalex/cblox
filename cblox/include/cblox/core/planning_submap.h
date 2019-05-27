#ifndef CBLOX_PLANNING_SUBMAP_H
#define CBLOX_PLANNING_SUBMAP_H

#include <cblox/core/tsdf_esdf_submap.h>
#include <voxblox/utils/planning_utils.h>
#include <voxblox_skeleton/skeleton.h>
#include <voxblox_skeleton/skeleton_generator.h>

namespace cblox {

class PlanningSubmap : public TsdfEsdfSubmap {
public:
  typedef std::shared_ptr<PlanningSubmap> Ptr;
  typedef std::shared_ptr<const PlanningSubmap> ConstPtr;

  PlanningSubmap(Config config)
      : TsdfEsdfSubmap(config),
        skeleton_generator_(esdf_map_->getEsdfLayerPtr()) { }

  PlanningSubmap(const Transformation& T_M_S, SubmapID submap_id, Config config)
      : TsdfEsdfSubmap(T_M_S, submap_id, config),
        skeleton_generator_(esdf_map_->getEsdfLayerPtr()) { }

  // map functions
  void computeMapBounds();
  void getMapBounds(Eigen::Vector3d* lower_bound, Eigen::Vector3d* upper_bound) {
    *lower_bound = lower_bound_;
    *upper_bound = upper_bound_;
  }
  void getGlobalMapBounds(Eigen::Vector3d* lower_bound,
                          Eigen::Vector3d* upper_bound);

  // skeleton functions
  void generateSkeleton() {
    skeleton_generator_.generateSkeleton();
  }
  void generateSparseGraph() {
    skeleton_generator_.generateSparseGraph();
  }

  // get functions
  voxblox::SkeletonGenerator* getSkeletonGenerator() {
    return &skeleton_generator_;
  }

 private:
  Eigen::Vector3d lower_bound_;
  Eigen::Vector3d upper_bound_;

  voxblox::SkeletonGenerator skeleton_generator_;
};

} // namespace cblox
#endif //CBLOX_PLANNING_SUBMAP_H