#ifndef PULSAR_GUARD_COMMON__EIGENCOMMON_HPP_
#define PULSAR_GUARD_COMMON__EIGENCOMMON_HPP_

#include "pulsar/math/BlockByIrrepSpin.hpp"
#include "pulsar/math/TensorImpl.hpp"

#include <Eigen/Dense>

namespace pulsar {
namespace math {

class EigenMatrixImpl : public pulsar::math::MatrixDImpl
{
    public:

        /*! \brief For serialization only
         * 
         * \warning NOT FOR USE OUTSIDE OF SERIALIZATION
         * \todo Replace if cereal fixes this
         */
        EigenMatrixImpl() = default;

        EigenMatrixImpl(const std::shared_ptr<Eigen::MatrixXd> & mat)
            : mat_(mat) { }

        EigenMatrixImpl(const Eigen::MatrixXd & mat)
            : mat_(std::make_shared<Eigen::MatrixXd>(mat)) { }

        EigenMatrixImpl(Eigen::MatrixXd && mat)
            : mat_(std::make_shared<Eigen::MatrixXd>(std::move(mat))) { }

        virtual std::array<size_t, 2> sizes(void) const
        {
            return {static_cast<size_t>((*mat_).rows()),
                    static_cast<size_t>((*mat_).cols())};
        }

        virtual double get_value(std::array<size_t, 2> idx) const
        {
            return (*mat_)(idx[0], idx[1]);
        }

        virtual void set_value(std::array<size_t, 2> idx, double val)
        {
            (*mat_)(idx[0], idx[1]) = val;
        }

        std::shared_ptr<const Eigen::MatrixXd>
        get_matrix(void) const
        {
            return mat_;
        }

    private:
        std::shared_ptr<Eigen::MatrixXd> mat_;

        DECLARE_SERIALIZATION_FRIENDS

        template<class Archive>
        void save(Archive & archive) const
        {
            archive(cereal::base_class<pulsar::math::MatrixDImpl>(this));
            unsigned int nrow = mat_->rows();
            unsigned int ncol = mat_->cols();

            archive(nrow, ncol);

            //! \todo slow
            for(unsigned int i = 0; i < nrow; i++)
            for(unsigned int j = 0; j < ncol; j++)
                archive((*mat_)(i,j));
        }

        template<class Archive>
        void load(Archive & archive)
        {
            archive(cereal::base_class<pulsar::math::MatrixDImpl>(this));

            unsigned int nrow, ncol;
            archive(nrow, ncol);

            mat_ = std::make_shared<Eigen::MatrixXd>(nrow, ncol);

            //! \todo slow
            for(unsigned int i = 0; i < nrow; i++)
            for(unsigned int j = 0; j < ncol; j++)
                archive((*mat_)(i,j));
        }
};


class EigenVectorImpl : public pulsar::math::VectorDImpl
{
    public:
        /*! \brief For serialization only
         * 
         * \warning NOT FOR USE OUTSIDE OF SERIALIZATION
         * \todo Replace if cereal fixes this
         */
        EigenVectorImpl() = default;

        EigenVectorImpl(const std::shared_ptr<Eigen::VectorXd> & mat)
            : mat_(mat) { }

        EigenVectorImpl(const Eigen::VectorXd & mat)
            : mat_(std::make_shared<Eigen::VectorXd>(mat)) { }

        EigenVectorImpl(Eigen::VectorXd && mat)
            : mat_(std::make_shared<Eigen::VectorXd>(std::move(mat))) { }

        virtual std::array<size_t, 1> sizes(void) const
        {
            return {static_cast<size_t>((*mat_).size())};
        }

        virtual double get_value(std::array<size_t, 1> idx) const
        {
            return (*mat_)(idx[0]);
        }

        virtual void set_value(std::array<size_t, 1> idx, double val)
        {
            (*mat_)(idx[0]) = val;
        }

        std::shared_ptr<const Eigen::VectorXd>
        get_matrix(void) const
        {
            return mat_;
        }

    private:
        std::shared_ptr<Eigen::VectorXd> mat_;


        DECLARE_SERIALIZATION_FRIENDS

        template<class Archive>
        void save(Archive & archive) const
        {
            archive(cereal::base_class<pulsar::math::VectorDImpl>(this));
            unsigned int nrow = mat_->rows();
            unsigned int ncol = mat_->cols();

            archive(nrow, ncol);

            //! \todo slow
            for(unsigned int i = 0; i < nrow; i++)
            for(unsigned int j = 0; j < ncol; j++)
                archive((*mat_)(i,j));
        }

        template<class Archive>
        void load(Archive & archive)
        {
            archive(cereal::base_class<pulsar::math::VectorDImpl>(this));

            unsigned int nrow, ncol;
            archive(nrow, ncol);

            mat_ = std::make_shared<Eigen::VectorXd>(nrow, ncol);

            //! \todo slow
            for(unsigned int i = 0; i < nrow; i++)
            for(unsigned int j = 0; j < ncol; j++)
                archive((*mat_)(i,j));
        }
};


std::shared_ptr<const Eigen::MatrixXd>
convert_to_eigen(const std::shared_ptr<const pulsar::math::MatrixDImpl> & ten);

std::shared_ptr<const Eigen::VectorXd>
convert_to_eigen(const std::shared_ptr<const pulsar::math::VectorDImpl> & ten);


typedef pulsar::math::BlockByIrrepSpin<Eigen::MatrixXd> BlockedEigenMatrix;
typedef pulsar::math::BlockByIrrepSpin<Eigen::VectorXd> BlockedEigenVector;


} // close namespace math
} // close namespace pulsar

#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>

CEREAL_REGISTER_TYPE(pulsar::math::EigenMatrixImpl);
CEREAL_REGISTER_TYPE(pulsar::math::EigenVectorImpl);
CEREAL_REGISTER_POLYMORPHIC_RELATION(pulsar::math::MatrixDImpl,pulsar::math::EigenMatrixImpl);
CEREAL_REGISTER_POLYMORPHIC_RELATION(pulsar::math::VectorDImpl,pulsar::math::EigenVectorImpl);

#endif

