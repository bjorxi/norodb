# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
#
# For macos Catalina and Vagrant 2.2.19 check this https://github.com/hashicorp/vagrant/issues/12583
#
Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/focal64"
  config.vm.box_check_update = false
  # config.vm.network :private_network, ip: "192.168.50.50"

  nfsPath = "."
  # if Dir.exist?("/System/Volumes/Data")
  #     nfsPath = "/System/Volumes/Data" + Dir.pwd
  # end
  # config.vm.synced_folder nfsPath, "/vagrant", type: "nfs"

  config.vm.provider "virtualbox" do |vb|
    vb.gui = false
    vb.cpus = 2
    vb.memory = "2048"
  end

  config.vm.provision "shell", inline: <<-SHELL
    apt-get update
    apt-get install -y build-essential clang-format git cmake
    cd /vagrant/test/third_party/googletest && cmake CMakeLists.txt && make install
  SHELL
end
