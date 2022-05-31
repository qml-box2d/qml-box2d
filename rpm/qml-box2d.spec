Name:       qml-box2d

Summary:    Box 2D QML module
Version:    0.0.0
Release:    1
Group:      System/Libraries
License:    zlib
URL:        https://github.com/qml-box2d/qml-box2d
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)

%description
%{summary}.

%prep
%setup -q -n %{name}-%{version}

%build

%qmake5

make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%qmake5_install

%files
%defattr(-,root,root,-)
%{_libdir}/qt5/qml/Box2D.2.0/libBox2D.so
%{_libdir}/qt5/qml/Box2D.2.0/qmldir
