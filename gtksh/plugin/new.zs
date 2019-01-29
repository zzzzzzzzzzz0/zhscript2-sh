#!/usr/lib/zhscript2/l --。
解释下代码
模块文件。
赋予.cproject以
下原样<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<?fileVersion 4.0.0?><cproject storage_type_id="org.eclipse.cdt.core.XmlProjectDescriptionStorage">
	<storageModule moduleId="org.eclipse.cdt.core.settings">
		<cconfiguration id="cdt.managedbuild.config.gnu.so.debug.调数01">
			<storageModule buildSystemId="org.eclipse.cdt.managedbuilder.core.configurationDataProvider" id="cdt.managedbuild.config.gnu.so.debug.调数01" moduleId="org.eclipse.cdt.core.settings" name="Debug">
				<externalSettings>
					<externalSetting>
						<entry flags="VALUE_WORKSPACE_PATH" kind="includePath" name="/gtksh-plugin-插件名"/>
						<entry flags="VALUE_WORKSPACE_PATH" kind="libraryPath" name="/gtksh-plugin-插件名/Debug"/>
						<entry flags="RESOLVED" kind="libraryFile" name="插件名" srcPrefixMapping="" srcRootPath=""/>
					</externalSetting>
				</externalSettings>
				<extensions>
					<extension id="org.eclipse.cdt.core.GNU_ELF" point="org.eclipse.cdt.core.BinaryParser"/>
					<extension id="org.eclipse.cdt.core.GASErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.GmakeErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.GLDErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.CWDLocator" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.GCCErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
				</extensions>
			</storageModule>
			<storageModule moduleId="cdtBuildSystem" version="4.0.0">
				<configuration artifactExtension="so" artifactName="插件名" buildArtefactType="org.eclipse.cdt.build.core.buildArtefactType.sharedLib" buildProperties="org.eclipse.cdt.build.core.buildArtefactType=org.eclipse.cdt.build.core.buildArtefactType.sharedLib,org.eclipse.cdt.build.core.buildType=org.eclipse.cdt.build.core.buildType.debug" cleanCommand="rm -rf" description="" id="cdt.managedbuild.config.gnu.so.debug.调数01" name="Debug" parent="cdt.managedbuild.config.gnu.so.debug">
					<folderInfo id="cdt.managedbuild.config.gnu.so.debug.调数01." name="/" resourcePath="">
						<toolChain id="cdt.managedbuild.toolchain.gnu.so.debug.调数02" name="Linux GCC" superClass="cdt.managedbuild.toolchain.gnu.so.debug">
							<targetPlatform id="cdt.managedbuild.target.gnu.platform.so.debug.调数03" name="Debug Platform" superClass="cdt.managedbuild.target.gnu.platform.so.debug"/>
							<builder buildPath="${workspace_loc:/gtksh-plugin-插件名}/Debug" id="cdt.managedbuild.target.gnu.builder.so.debug.调数04" keepEnvironmentInBuildfile="false" managedBuildOn="true" name="Gnu Make Builder" superClass="cdt.managedbuild.target.gnu.builder.so.debug"/>
							<tool commandLinePattern="${COMMAND} ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS} 库包参" id="cdt.managedbuild.tool.gnu.archiver.base.调数05" name="GCC Archiver" superClass="cdt.managedbuild.tool.gnu.archiver.base"/>
							<tool command="g++" commandLinePattern="${COMMAND} ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS} 细包参" id="cdt.managedbuild.tool.gnu.cpp.compiler.so.debug.调数06" name="GCC C++ Compiler" superClass="cdt.managedbuild.tool.gnu.cpp.compiler.so.debug">
								<option id="gnu.cpp.compiler.so.debug.option.optimization.level.调数10" name="Optimization Level" superClass="gnu.cpp.compiler.so.debug.option.optimization.level" useByScannerDiscovery="false" value="gnu.cpp.compiler.optimization.level.none" valueType="enumerated"/>
								<option id="gnu.cpp.compiler.so.debug.option.debugging.level.调数11" name="Debug Level" superClass="gnu.cpp.compiler.so.debug.option.debugging.level" useByScannerDiscovery="false" value="gnu.cpp.compiler.debugging.level.max" valueType="enumerated"/>
								<option id="gnu.cpp.compiler.option.dialect.std.调数12" name="Language standard" superClass="gnu.cpp.compiler.option.dialect.std" useByScannerDiscovery="true" value="gnu.cpp.compiler.dialect.c++1y" valueType="enumerated"/>
								<option id="gnu.cpp.compiler.option.other.pic.调数13" name="Position Independent Code (-fPIC)" superClass="gnu.cpp.compiler.option.other.pic" useByScannerDiscovery="false" value="true" valueType="boolean"/>
								<inputType id="cdt.managedbuild.tool.gnu.cpp.compiler.input.调数07" superClass="cdt.managedbuild.tool.gnu.cpp.compiler.input"/>
							</tool>
							<tool id="cdt.managedbuild.tool.gnu.c.compiler.so.debug.调数09" name="GCC C Compiler" superClass="cdt.managedbuild.tool.gnu.c.compiler.so.debug">
								<option defaultValue="gnu.c.optimization.level.none" id="gnu.c.compiler.so.debug.option.optimization.level.调数23" name="Optimization Level" superClass="gnu.c.compiler.so.debug.option.optimization.level" useByScannerDiscovery="false" valueType="enumerated"/>
								<option id="gnu.c.compiler.so.debug.option.debugging.level.调数14" name="Debug Level" superClass="gnu.c.compiler.so.debug.option.debugging.level" useByScannerDiscovery="false" value="gnu.c.debugging.level.max" valueType="enumerated"/>
								<inputType id="cdt.managedbuild.tool.gnu.c.compiler.input.调数08" superClass="cdt.managedbuild.tool.gnu.c.compiler.input"/>
							</tool>
							<tool commandLinePattern="${COMMAND} ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS} 库包参" id="cdt.managedbuild.tool.gnu.c.linker.so.debug.调数16" name="GCC C Linker" superClass="cdt.managedbuild.tool.gnu.c.linker.so.debug">
								<option defaultValue="true" id="gnu.c.link.so.debug.option.shared.调数15" name="Shared (-shared)" superClass="gnu.c.link.so.debug.option.shared" valueType="boolean"/>
							</tool>
							<tool command="g++" commandLinePattern="${COMMAND} ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS} 库包参" id="cdt.managedbuild.tool.gnu.cpp.linker.so.debug.调数21" name="GCC C++ Linker" superClass="cdt.managedbuild.tool.gnu.cpp.linker.so.debug">
								<option defaultValue="true" id="gnu.cpp.link.so.debug.option.shared.调数17" name="Shared (-shared)" superClass="gnu.cpp.link.so.debug.option.shared" useByScannerDiscovery="false" valueType="boolean"/>
								<inputType id="cdt.managedbuild.tool.gnu.cpp.linker.input.调数22" superClass="cdt.managedbuild.tool.gnu.cpp.linker.input">
									<additionalInput kind="additionalinputdependency" paths="$(USER_OBJS)"/>
									<additionalInput kind="additionalinput" paths="$(LIBS)"/>
								</inputType>
								<outputType id="cdt.managedbuild.tool.gnu.cpp.linker.so.debug.output.调数18" outputPrefix="../../../../../bin/zhscript2/gtksh-plugin/" superClass="cdt.managedbuild.tool.gnu.cpp.linker.so.debug.output"/>
							</tool>
							<tool id="cdt.managedbuild.tool.gnu.assembler.so.debug.调数19" name="GCC Assembler" superClass="cdt.managedbuild.tool.gnu.assembler.so.debug">
								<inputType id="cdt.managedbuild.tool.gnu.assembler.input.调数20" superClass="cdt.managedbuild.tool.gnu.assembler.input"/>
							</tool>
						</toolChain>
					</folderInfo>
				</configuration>
			</storageModule>
			<storageModule moduleId="org.eclipse.cdt.core.externalSettings"/>
		</cconfiguration>
		<cconfiguration id="cdt.managedbuild.config.gnu.so.release.发数01">
			<storageModule buildSystemId="org.eclipse.cdt.managedbuilder.core.configurationDataProvider" id="cdt.managedbuild.config.gnu.so.release.发数01" moduleId="org.eclipse.cdt.core.settings" name="Release">
				<externalSettings>
					<externalSetting>
						<entry flags="VALUE_WORKSPACE_PATH" kind="includePath" name="/gtksh-plugin-插件名"/>
						<entry flags="VALUE_WORKSPACE_PATH" kind="libraryPath" name="/gtksh-plugin-插件名/Release"/>
						<entry flags="RESOLVED" kind="libraryFile" name="插件名" srcPrefixMapping="" srcRootPath=""/>
					</externalSetting>
				</externalSettings>
				<extensions>
					<extension id="org.eclipse.cdt.core.GNU_ELF" point="org.eclipse.cdt.core.BinaryParser"/>
					<extension id="org.eclipse.cdt.core.GASErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.GmakeErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.GLDErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.CWDLocator" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.GCCErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
				</extensions>
			</storageModule>
			<storageModule moduleId="cdtBuildSystem" version="4.0.0">
				<configuration artifactExtension="so" artifactName="插件名" buildArtefactType="org.eclipse.cdt.build.core.buildArtefactType.sharedLib" buildProperties="org.eclipse.cdt.build.core.buildArtefactType=org.eclipse.cdt.build.core.buildArtefactType.sharedLib,org.eclipse.cdt.build.core.buildType=org.eclipse.cdt.build.core.buildType.release" cleanCommand="rm -rf" description="" id="cdt.managedbuild.config.gnu.so.release.发数01" name="Release" parent="cdt.managedbuild.config.gnu.so.release">
					<folderInfo id="cdt.managedbuild.config.gnu.so.release.发数01." name="/" resourcePath="">
						<toolChain id="cdt.managedbuild.toolchain.gnu.so.release.发数02" name="Linux GCC" superClass="cdt.managedbuild.toolchain.gnu.so.release">
							<targetPlatform id="cdt.managedbuild.target.gnu.platform.so.release.发数03" name="Debug Platform" superClass="cdt.managedbuild.target.gnu.platform.so.release"/>
							<builder buildPath="${workspace_loc:/gtksh-plugin-插件名}/Release" id="cdt.managedbuild.target.gnu.builder.so.release.发数04" keepEnvironmentInBuildfile="false" managedBuildOn="true" name="Gnu Make Builder" superClass="cdt.managedbuild.target.gnu.builder.so.release"/>
							<tool commandLinePattern="${COMMAND} ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS} 库包参" id="cdt.managedbuild.tool.gnu.archiver.base.发数05" name="GCC Archiver" superClass="cdt.managedbuild.tool.gnu.archiver.base"/>
							<tool commandLinePattern="${COMMAND} ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS} 细包参" id="cdt.managedbuild.tool.gnu.cpp.compiler.so.release.发数06" name="GCC C++ Compiler" superClass="cdt.managedbuild.tool.gnu.cpp.compiler.so.release">
								<option id="gnu.cpp.compiler.so.release.option.optimization.level.发数07" name="Optimization Level" superClass="gnu.cpp.compiler.so.release.option.optimization.level" useByScannerDiscovery="false" value="gnu.cpp.compiler.optimization.level.most" valueType="enumerated"/>
								<option id="gnu.cpp.compiler.so.release.option.debugging.level.发数08" name="Debug Level" superClass="gnu.cpp.compiler.so.release.option.debugging.level" useByScannerDiscovery="false" value="gnu.cpp.compiler.debugging.level.none" valueType="enumerated"/>
								<option id="gnu.cpp.compiler.option.dialect.std.发数09" name="Language standard" superClass="gnu.cpp.compiler.option.dialect.std" useByScannerDiscovery="true" value="gnu.cpp.compiler.dialect.c++1y" valueType="enumerated"/>
								<option id="gnu.cpp.compiler.option.other.pic.发数10" name="Position Independent Code (-fPIC)" superClass="gnu.cpp.compiler.option.other.pic" useByScannerDiscovery="false" value="true" valueType="boolean"/>
								<inputType id="cdt.managedbuild.tool.gnu.cpp.compiler.input.发数11" superClass="cdt.managedbuild.tool.gnu.cpp.compiler.input"/>
							</tool>
							<tool id="cdt.managedbuild.tool.gnu.c.compiler.so.release.发数12" name="GCC C Compiler" superClass="cdt.managedbuild.tool.gnu.c.compiler.so.release">
								<option defaultValue="gnu.c.optimization.level.most" id="gnu.c.compiler.so.release.option.optimization.level.发数13" name="Optimization Level" superClass="gnu.c.compiler.so.release.option.optimization.level" useByScannerDiscovery="false" valueType="enumerated"/>
								<option id="gnu.c.compiler.so.release.option.debugging.level.发数14" name="Debug Level" superClass="gnu.c.compiler.so.release.option.debugging.level" useByScannerDiscovery="false" value="gnu.c.debugging.level.none" valueType="enumerated"/>
								<inputType id="cdt.managedbuild.tool.gnu.c.compiler.input.发数15" superClass="cdt.managedbuild.tool.gnu.c.compiler.input"/>
							</tool>
							<tool commandLinePattern="${COMMAND} ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS} 库包参" id="cdt.managedbuild.tool.gnu.c.linker.so.release.发数16" name="GCC C Linker" superClass="cdt.managedbuild.tool.gnu.c.linker.so.release">
								<option defaultValue="true" id="gnu.c.link.so.release.option.shared.发数17" name="Shared (-shared)" superClass="gnu.c.link.so.release.option.shared" valueType="boolean"/>
							</tool>
							<tool commandLinePattern="${COMMAND} ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS} 库包参" id="cdt.managedbuild.tool.gnu.cpp.linker.so.release.发数18" name="GCC C++ Linker" superClass="cdt.managedbuild.tool.gnu.cpp.linker.so.release">
								<option defaultValue="true" id="gnu.cpp.link.so.release.option.shared.发数19" name="Shared (-shared)" superClass="gnu.cpp.link.so.release.option.shared" useByScannerDiscovery="false" valueType="boolean"/>
								<inputType id="cdt.managedbuild.tool.gnu.cpp.linker.input.发数20" superClass="cdt.managedbuild.tool.gnu.cpp.linker.input">
									<additionalInput kind="additionalinputdependency" paths="$(USER_OBJS)"/>
									<additionalInput kind="additionalinput" paths="$(LIBS)"/>
								</inputType>
								<outputType id="cdt.managedbuild.tool.gnu.cpp.linker.so.release.output.发数21" outputPrefix="../../../../bin-r/gtksh-plugin/" superClass="cdt.managedbuild.tool.gnu.cpp.linker.so.release.output"/>
							</tool>
							<tool id="cdt.managedbuild.tool.gnu.assembler.so.release.发数22" name="GCC Assembler" superClass="cdt.managedbuild.tool.gnu.assembler.so.release">
								<inputType id="cdt.managedbuild.tool.gnu.assembler.input.发数23" superClass="cdt.managedbuild.tool.gnu.assembler.input"/>
							</tool>
						</toolChain>
					</folderInfo>
				</configuration>
			</storageModule>
			<storageModule moduleId="org.eclipse.cdt.core.externalSettings"/>
		</cconfiguration>
	</storageModule>
	<storageModule moduleId="cdtBuildSystem" version="4.0.0">
		<project id="gtksh-plugin-插件名.cdt.managedbuild.target.gnu.so.发数41" name="Shared Library" projectType="cdt.managedbuild.target.gnu.so"/>
	</storageModule>
	<storageModule moduleId="scannerConfiguration">
		<autodiscovery enabled="true" problemReportingEnabled="true" selectedProfileId=""/>
		<scannerConfigBuildInfo instanceId="cdt.managedbuild.config.gnu.so.release.发数01;cdt.managedbuild.config.gnu.so.release.发数01.;cdt.managedbuild.tool.gnu.c.compiler.so.release.发数12;cdt.managedbuild.tool.gnu.c.compiler.input.发数15">
			<autodiscovery enabled="true" problemReportingEnabled="true" selectedProfileId=""/>
		</scannerConfigBuildInfo>
		<scannerConfigBuildInfo instanceId="cdt.managedbuild.config.gnu.so.debug.调数01;cdt.managedbuild.config.gnu.so.debug.调数01.;cdt.managedbuild.tool.gnu.c.compiler.so.debug.调数09;cdt.managedbuild.tool.gnu.c.compiler.input.调数08">
			<autodiscovery enabled="true" problemReportingEnabled="true" selectedProfileId=""/>
		</scannerConfigBuildInfo>
		<scannerConfigBuildInfo instanceId="cdt.managedbuild.config.gnu.so.debug.调数01;cdt.managedbuild.config.gnu.so.debug.调数01.;cdt.managedbuild.tool.gnu.cpp.compiler.so.debug.调数06;cdt.managedbuild.tool.gnu.cpp.compiler.input.调数07">
			<autodiscovery enabled="true" problemReportingEnabled="true" selectedProfileId=""/>
		</scannerConfigBuildInfo>
		<scannerConfigBuildInfo instanceId="cdt.managedbuild.config.gnu.so.release.发数01;cdt.managedbuild.config.gnu.so.release.发数01.;cdt.managedbuild.tool.gnu.cpp.compiler.so.release.发数06;cdt.managedbuild.tool.gnu.cpp.compiler.input.发数11">
			<autodiscovery enabled="true" problemReportingEnabled="true" selectedProfileId=""/>
		</scannerConfigBuildInfo>
	</storageModule>
	<storageModule moduleId="org.eclipse.cdt.core.LanguageSettingsProviders"/>
	<storageModule moduleId="refreshScope"/>
	<storageModule moduleId="org.eclipse.cdt.make.core.buildtargets"/>
</cproject>上原样。
赋予.project以
下原样<?xml version="1.0" encoding="UTF-8"?>
<projectDescription>
	<name>gtksh-plugin-插件名</name>
	<comment></comment>
	<projects>
	</projects>
	<buildSpec>
		<buildCommand>
			<name>org.eclipse.cdt.managedbuilder.core.genmakebuilder</name>
			<triggers>clean,full,incremental,</triggers>
			<arguments>
			</arguments>
		</buildCommand>
		<buildCommand>
			<name>org.eclipse.cdt.managedbuilder.core.ScannerConfigBuilder</name>
			<triggers>full,incremental,</triggers>
			<arguments>
			</arguments>
		</buildCommand>
	</buildSpec>
	<natures>
		<nature>org.eclipse.cdt.core.cnature</nature>
		<nature>org.eclipse.cdt.core.ccnature</nature>
		<nature>org.eclipse.cdt.managedbuilder.core.managedBuildNature</nature>
		<nature>org.eclipse.cdt.managedbuilder.core.ScannerConfigNature</nature>
	</natures>
</projectDescription>上原样。
赋予.settings/language.settings.xml以
下原样<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<project>
	<configuration id="cdt.managedbuild.config.gnu.so.debug.调数01" name="Debug">
		<extension point="org.eclipse.cdt.core.LanguageSettingsProvider">
			<provider copy-of="extension" id="org.eclipse.cdt.ui.UserLanguageSettingsProvider"/>
			<provider-reference id="org.eclipse.cdt.core.ReferencedProjectsLanguageSettingsProvider" ref="shared-provider"/>
			<provider-reference id="org.eclipse.cdt.managedbuilder.core.MBSLanguageSettingsProvider" ref="shared-provider"/>
			<provider class="org.eclipse.cdt.managedbuilder.language.settings.providers.GCCBuiltinSpecsDetector" console="false" env-hash="-发数42" id="org.eclipse.cdt.managedbuilder.core.GCCBuiltinSpecsDetector" keep-relative-paths="false" name="CDT GCC Built-in Compiler Settings" parameter="${COMMAND} ${FLAGS} -E -P -v -dD &quot;${INPUTS}&quot;" prefer-non-shared="true">
				<language-scope id="org.eclipse.cdt.core.gcc"/>
				<language-scope id="org.eclipse.cdt.core.g++"/>
			</provider>
		</extension>
	</configuration>
	<configuration id="cdt.managedbuild.config.gnu.so.release.发数01" name="Release">
		<extension point="org.eclipse.cdt.core.LanguageSettingsProvider">
			<provider copy-of="extension" id="org.eclipse.cdt.ui.UserLanguageSettingsProvider"/>
			<provider-reference id="org.eclipse.cdt.core.ReferencedProjectsLanguageSettingsProvider" ref="shared-provider"/>
			<provider-reference id="org.eclipse.cdt.managedbuilder.core.MBSLanguageSettingsProvider" ref="shared-provider"/>
			<provider class="org.eclipse.cdt.managedbuilder.language.settings.providers.GCCBuiltinSpecsDetector" console="false" env-hash="-发数42" id="org.eclipse.cdt.managedbuilder.core.GCCBuiltinSpecsDetector" keep-relative-paths="false" name="CDT GCC Built-in Compiler Settings" parameter="${COMMAND} ${FLAGS} -E -P -v -dD &quot;${INPUTS}&quot;" prefer-non-shared="true">
				<language-scope id="org.eclipse.cdt.core.gcc"/>
				<language-scope id="org.eclipse.cdt.core.g++"/>
			</provider>
		</extension>
	</configuration>
</project>上原样。
赋予插件名.cpp以
下原样/*
 * 插件名.cpp
 *
 *  Created on: 建立日期
 *      Author: 作者
 */

#include "插件名.h"
#include "view.h"

pub::view___* 插件名___::new_view__() {
	return new view___();
}

插件名___::插件名___() {
}

插件名___::~插件名___() {
}

static 插件名___ plugin_;
extern "C" void *plugin__(const std::string &path) {return &plugin_;}
上原样。
赋予插件名.h以
下原样/*
 * 插件名.h
 *
 *  Created on: 建立日期
 *      Author: 作者
 */

#ifndef 插件大写名_H_
#define 插件大写名_H_

#include "pub/plugin.h"

class 插件名___: public pub::plugin___ {
public:
	插件名___();
	virtual ~插件名___();

	pub::view___* new_view__();
};

#endif /* 插件大写名_H_ */上原样。
赋予view.cpp以
下原样/*
 * view.cpp
 *
 *  Created on: 建立日期
 *      Author: 作者
 */

#include "view.h"
#include "pub/sig.h"
#include "pub/tag.h"
#include "pub/ext.h"
#include "pub/plugin.h"
#include "插件名.h"

static 插件名___ *plugin_ = nullptr;

static pub::tags___ tags_ = {
		//{"内容", " ", 1},
};

bool view___::api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret) {
	std::string tag;
	switch(tags_.get__(p, tag)) {
	case 'y':
		switch(tag[0]) {
		case ' ':
			break;
		}
		return true;
	case '<':
		pub::ext_->buzu__(p, SIZE_MAX);
		return true;
	}
	return pub::view___::api__(shangji, p, p2, ret);
}

void view___::new_open__(const std::vector<std::string>& p) {
}

static pub::sigs___ sigs_ = {
		//{"create", G_CALLBACK(cb_create__), "新开"},
};

view___::view___() {
	//hr_ = 

	sigs_.conn__(hr_, this);
}

view___::~view___() {
}

extern "C" void ext__(pub::ext___* ext, pub::plugin___ *plugin) {
	pub::ext_ = ext;
	plugin_ = (插件名___ *)plugin;
}
上原样。
赋予view.h以
下原样/*
 * view.h
 *
 *  Created on: 建立日期
 *      Author: 作者
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "pub/view.h"

class view___: public pub::view___ {
public:
	view___();
	virtual ~view___();

	bool api__(void* shangji, const std::vector<std::string>& p, std::vector<pub::data___>* p2, std::vector<std::string>& ret);
	void new_open__(const std::vector<std::string>& p);
};

#endif /* VIEW_H_ */上原样。
上代码。

解释下代码
	模块设置。
	赋予库包参、细包参以。
上代码。

赋予作者以zzzzzzzzzzz。
赋予包以gtk+-3.0。

加载lib/clpars4。
调用‘命令行加回调’、
	-n、下代码
		赋予插件名【设置】以‘参数1’
	上代码、1、、
	-p、“依赖包（pkg-config 包名。默认 ‘包’）”、1、下代码
		赋予包【上】以“‘包’ ‘参数1’”
	上代码、
	-ov、“是否覆盖（默认否）”、0、下代码
		赋予‘参数0’【上】以‘参数1’
	上代码、
	-zz、“作者（默认 ‘作者’）”、1、下代码
		赋予作者【上】以‘参数1’
	上代码。
调用‘命令行解析’、‘参数栈’。

如果不存在插件名【设置】那么
	调用‘命令行解析’、-h。

加载lib/doscmd4。
如果调用‘existdir’、‘插件名’并且不存在-ov那么显示“‘插件名’ 已存在”换行，结束1。

加载lib/gjk4。
赋予插件大写名【设置】以调用‘大写方法’、‘插件名’。
如果‘包’那么
	赋予库包参【设置】以“`pkg-config --libs ”  ‘包’`，
	赋予细包参【设置】以“`pkg-config --cflags ”‘包’`。
赋予调数【设置】以调用‘串格时间’、%y%m%d%H%M%S。
赋予发数【设置】以算术‘调数’+1。
赋予建立日期以先调用‘串格时间’、%Y年%m月%d日了。

加载lib/gjke4。
调用‘迭代二’、下代码
	别名名以参数1。
	显示‘名’TAB‘‘名’’换行
上代码、1、
插件大写名、库包参、细包参、调数、发数、建立日期。

加载lib/forqv。
调用‘遍历变量’、‘变量区【文件】’、下代码
	（显示‘参数’换行。）
	别名名、值以参数1、参数2。
	调用‘遍历变量名’、‘变量区【设置】’、下代码
		（显示‘参数’换行。）
		别名名2以参数1。
		赋予名【上】以调用‘多串替换’、‘名’、‘名2’、““‘‘名2’’””。
		赋予值【上】以调用‘多串替换’、‘值’、‘名2’、““‘‘名2’’””。
	上代码。
	显示‘名’换行。
	赋予值以调用‘多串替换’、‘值’、
		建立日期、‘建立日期’、
		作者、‘作者’。
	赋予以调用‘echo’、‘值’、‘插件名’/‘名’。
上代码。

加载lib/file4。
调用‘建符号链接’、../../main/pub、‘插件名’/pub、1。
