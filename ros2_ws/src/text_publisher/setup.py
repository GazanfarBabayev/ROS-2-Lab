from setuptools import find_packages, setup

package_name = 'text_publisher'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Gazanfar Babayev',
    maintainer_email='babayevgazanfar@gmail.com',
    description='ROS 2 Publisher that publishes Custom Message type',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "cstm_msg_pub = text_publisher.publisher:main"
        ],
    },
)
